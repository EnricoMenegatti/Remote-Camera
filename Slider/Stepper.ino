
void Stepper_Setup()
{
  Serial.println("Stepper setup");
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(500);
  Serial.println("Stepper setup OK");
}

void Stepper_Run(String Dir, String Vel, String Step)
{
  Serial.println("Stepper_Run");
  long relative_step;
  
  if(Dir == "A")//antiorario
  {
    relative_step = -Step.toInt();
  }
  else if(Dir == "O")//orario
  {
    relative_step = Step.toInt();
  }
  else//non valido
  {
    
  }
  stepper.setSpeed(Vel.toInt());
  stepper.move(relative_step);

  Serial.println(Vel.toInt());
  Serial.println(relative_step);
  Serial.println(Step.toInt());
  
  //stepper.runToPosition();
  run_step = 1;
  
}

