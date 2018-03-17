 int p_CLK = 7;  // Connected to CLK on KY-040
 int p_DT = 6;  // Connected to DT on KY-040
 int p_SW = 5;
 int Enc_count = 0; 
 int CLK_Last;  
 int CLK_Val;
 boolean bCW;

 void setup() { 
   pinMode (p_CLK,INPUT);
   pinMode (p_DT,INPUT);
   pinMode (p_SW,INPUT);
   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
   CLK_Last = digitalRead(p_CLK);   
   Serial.begin (9600);
 } 

 void loop() { 
   CLK_Val = digitalRead(p_CLK);
   if (CLK_Val != CLK_Last){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(p_DT) != CLK_Val) {  // Means pin A Changed first - We're Rotating Clockwise
       Enc_count ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       Enc_count --;
     }
     Serial.print ("Rotated: ");
     if (bCW){
       Serial.println ("clockwise");
     }else{
       Serial.println("counterclockwise");
     }
     Serial.print("Encoder Position: ");
     Serial.println(Enc_count);
     Serial.println(digitalRead(p_SW));
     
   } 
   CLK_Last = CLK_Val;
 }
