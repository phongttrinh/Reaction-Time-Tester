//Phong Trinh
int val;          //creates a variable integer called 'val' 
int rep;         //creates a variable integer called 'rep' 
int randTime = 0; //creates a variable integer called 'randTime and starting 0' 
int timer1_counter; //creates a variable integer called 'timer1_counter'
int int_flag = 0;       // Flag that indicates a timer interrupt has occured
int ReactionTime; //creates a variable integer called "ReactionTime'


void setup() {

Serial.begin(9600);           //Initialize serial commmunications

pinMode(2, INPUT_PULLUP);        // set pin to input
pinMode(13, OUTPUT);            // sets the digital pin 13 as output
digitalWrite(13, LOW);         // sets the digital pin 13 off
val = 1;                      // initialize timer1 


noInterrupts();        // disable all interrupts
 TCCR1A = 0;
 TCCR1B = 0;
// Set timer1_counter to the correct value for our interrupt interval
timer1_counter = 49536;    // preload timer 65536-16MHz
  
 TCNT1 = timer1_counter;   // preload timer
 TCCR1B |= (1 << CS10);    // 256 prescaler 
 TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt

  
interrupts();             // enable all interrupts
}
ISR(TIMER1_OVF_vect)     // interrupt service routine 
{
TCNT1 = timer1_counter; // preload timer
  int_flag = 1;        // interrupt has ocurred
  ReactionTime ++;    // adds 1 to the sec on every loop   
}


void loop() {
 
for (rep = 0; rep <= 5; rep++) //set up for loop that turns on and off the LED    
   {
    digitalWrite(13, HIGH); // LED on
    delay(500);             // delay 500 milisec
    digitalWrite(13, LOW);  // LED off
    delay(500);            // delay 500 milisec
   }
     
  delay(3000+random(4000)); // delay 3000 milisec + a random munber of milisec 0 - 4000

  digitalWrite(13, HIGH);  // then turn on LED
  
  ReactionTime = 0;         // set up ReactionTime begin at zero
  
  while(val==1)             // Wait until button is pressed
  {
    val = digitalRead(2);   // read the input pin
    int_flag = 1;         // interrupt has ocurred
  }

while(val==0)               // Wait until button is released
  {
    val = digitalRead(2);   // read the input pin
    int_flag = 0;           // noInterrupts has ocurred
  }
  
 Serial.print("\n"); Serial.print("Reaction Time"); 
 // Display pharse 'Reaction Time ' in each line
 Serial.print(":"); Serial.print(ReactionTime);  
 // Print the reactionTime of users
}

 
