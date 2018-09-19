
void SPIFFS_Setup()
{
  SPIFFS.begin(); // Start the SPI Flash File System (SPIFFS)
  Serial.println("SPIFFS started. Contents:");
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) // List the file system contents
    { 
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }
}

bool handleFileRead(String path) // send the right file to the client (if it exists)
{
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html"; // If a folder is requested, send the index file
  
  String contentType = getContentType(path); // Get the MIME type
  String pathWithGz = path + ".gz";
  
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) // If the file exists, either as a compressed archive, or normal
  {
    if (SPIFFS.exists(pathWithGz)) // If there's a compressed version available
      path += ".gz"; // Use the compressed verion
      
    File file = SPIFFS.open(path, "r"); // Open the file
    size_t sent = server.streamFile(file, contentType); // Send it to the client
    file.close(); // Close the file again
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path); // If the file doesn't exist, return false
  return false;
}

void handleFileUpload() // upload a new file to the SPIFFS
{
  HTTPUpload& upload = server.upload();
  String path;
  
  if(upload.status == UPLOAD_FILE_START)
  {
    path = upload.filename;
    if(!path.startsWith("/")) path = "/"+path;
    
    if(!path.endsWith(".gz")) // The file server always prefers a compressed version of a file
    {
      String pathWithGz = path+".gz"; // So if an uploaded file is not compressed, the existing compressed
      if(SPIFFS.exists(pathWithGz)) // version of that file must be deleted (if it exists)
        SPIFFS.remove(pathWithGz);
    }
    Serial.print("handleFileUpload Name: "); Serial.println(path);
    fsUploadFile = SPIFFS.open(path, "w"); // Open the file for writing in SPIFFS (create if it doesn't exist)
    path = String();
  } 
  else if(upload.status == UPLOAD_FILE_WRITE)
  {
    if(fsUploadFile)
    fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
  } 
  else if(upload.status == UPLOAD_FILE_END)
  {
    if(fsUploadFile) // If the file was successfully created
    { 
      fsUploadFile.close(); // Close the file again
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
      server.sendHeader("Location","/success.html"); // Redirect the client to the success page
      server.send(303);
    } 
    else 
    {
      server.send(500, "text/plain", "500: couldn't create file");
    }
  }
}
 
