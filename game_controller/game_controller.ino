/*Arduino script that is used to get input from a joystick and two buttons 
and use bitshifting to send a readable int through the serial port
to a reciever that decodes the payload and uses the input accordingly */

int old_value_button = 1;
int old_value_button2 = 1;
int old_value_up = 1;
  
void setup() {
  //read from pins 4-9 on the arduino
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  //read input from buttons
  int left = digitalRead(4);
  int right = digitalRead(5);
  int down = digitalRead(6);
  int up = digitalRead(7);
  int button1 = digitalRead(8);
  int button2 = digitalRead(9);
 
  int payload = 0;
  
  //check directions
  if(left == 0) {
     payload = payload | (1 << 1);
  }
  if(right == 0) {
     payload = payload | (1 << 0);
  }
  if(down == 0) {
     payload = payload | (1 << 3);
  }
  if(up == 0 && old_value_up == 1) {
     payload = payload | (1 << 2);
  }
  old_value_up = up;

  //check other button inputs
  if(button1 == 0 && old_value_button == 1) {
     payload = payload | (1 << 4);
  }
  old_value_button = button1;
  if(button2 == 0 && old_value_button2 == 1) {
     payload = payload | (1 << 5);
  }
  old_value_button2 = button2;

  //send payload to serial port
  Serial.write(payload);

  delay(80);
}
