#define left_button A1
#define right_button A2
#define bottom_button A0

#define left_led 10
#define right_led 11

#define output_1 3 
#define output_2 2

bool output_1_active = false;
bool output_2_active = true;

byte led_brightness = 10;

uint32_t hold_duration = 1000000; //us

uint32_t left_button_timer, right_button_timer, bottom_button_timer;
bool left_button_in_active_cycle, right_button_in_active_cycle, bottom_button_in_active_cycle;

void setup()
{
  analogWrite(left_led, 0);
  analogWrite(right_led, 0);
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(bottom_button, INPUT_PULLUP);
  
  pinMode(output_1, OUTPUT); //keithley
  pinMode(output_2, OUTPUT); //gwinstek
  
  digitalWrite(output_1, !output_1_active);
  digitalWrite(output_2, !output_2_active);
}

void loop()
{
  while(true)
  {
    checkButtons();
    setOutputs();
  }
}

void checkButtons()
{
  if(left_button_in_active_cycle)
  {
    //check to see if the cycle is over
    if((uint32_t)((long)micros()-left_button_timer) >= hold_duration)
    {
      //timer elapsed. exit.
      left_button_in_active_cycle = false;
    }
  }

  //check the button. set flag if needed
  if(!digitalRead(left_button))
  {
    left_button_in_active_cycle = true;
    left_button_timer = micros();
  }

  if(right_button_in_active_cycle)
  {
    //check to see if the cycle is over
    if((uint32_t)((long)micros()-right_button_timer) >= hold_duration)
    {
      //timer elapsed. exit.
      right_button_in_active_cycle = false;
    }
  }

  //check the button. set flag if needed
  if(!digitalRead(right_button))
  {
    right_button_in_active_cycle = true;
    right_button_timer = micros();
  }

  if(bottom_button_in_active_cycle)
  {
    //check to see if the cycle is over
    if((uint32_t)((long)micros()-bottom_button_timer) >= hold_duration)
    {
      //timer elapsed. exit.
      bottom_button_in_active_cycle = false;
    }
  }

  //check the button. set flag if needed
  if(!digitalRead(bottom_button))
  {
    bottom_button_in_active_cycle = true;
    bottom_button_timer = micros();
  }
}

void setOutputs()
{
  if(left_button_in_active_cycle || bottom_button_in_active_cycle)
  {
    analogWrite(left_led, led_brightness);
    digitalWrite(output_1, output_1_active);
  }
  else
  {
    analogWrite(left_led, 0);
    digitalWrite(output_1, !output_1_active);
  }

  if(right_button_in_active_cycle || bottom_button_in_active_cycle)
  {
    analogWrite(right_led, led_brightness);
    digitalWrite(output_2, output_2_active);
  }
  else
  {
    analogWrite(right_led, 0);
    digitalWrite(output_2, !output_2_active);
  }
}
