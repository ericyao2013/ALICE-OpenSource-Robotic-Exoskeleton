#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;
char select_motor;
uint8_t motor = 0;
int serial = 0;
 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);  

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  Serial.begin(9600);     
  Serial.println("Motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number to select motor:");
  Serial.println("1. Motor1");
  Serial.println("2. Motor2");

  while(serial == 0){
    serial = Serial.available();
  }
    select_motor = Serial.read();
    if(select_motor == '1'){
      motor = MOTOR_1;
      Serial.println("Motor1 selected");
    }
    else if(select_motor == '2'){
      motor = MOTOR_2;
      Serial.println("Motor2 selected");
    }
    else{
      Serial.println("Invalid option entered for motor selection.");
    }
  
   
  Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("2. FORWARD");
  Serial.println("3. REVERSE");
  Serial.println("4. READ CURRENT");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();
}

void loop() 
{
  char user_input;   
  digitalWrite(EN_PIN_1, HIGH); //Enable Motor1
  digitalWrite(EN_PIN_2, HIGH); //Enable Motor2
  
    while(Serial.available()){    
      user_input = Serial.read(); //Read user input 
      if (user_input =='1')
      {
         Stop(motor);
      }
      else if(user_input =='2')
      {
        Forward(motor);
        delay(50);
        Stop(motor);
      }
      else if(user_input =='3')
      {
        Reverse(motor);
        delay(50);
        Stop(motor);
      }
      else if(user_input =='+')
      {
        IncreaseSpeed();
      }
      else if(user_input =='-')
      {
        DecreaseSpeed();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
    }
}

void Stop(int motor)
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(motor, usMotor_Status, 0);
}

void Forward(int motor)
{
  Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(motor, usMotor_Status, usSpeed);
}

void Reverse(int motor)
{
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(motor, usMotor_Status, usSpeed);
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;  
  }
  
  Serial.print("Speed +: ");
  Serial.println(usSpeed);
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
  
  Serial.print("Speed -: ");
  Serial.println(usSpeed);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 or 1), direction (cw or ccw) and pwm (0 - 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_2)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_2, pwm);
  }
}


