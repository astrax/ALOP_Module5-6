//i/o pin declarations
int rpin = 9;
int gpin = 10;
int bpin = 11;

//function prototypes
void solid(int r, int g, int b, int t);
void fade(int r1, int g1, int b1, int r2, int g2, int b2, int t);

void setup()                 
{
//empty
}

void loop()                     
{
 //colour sequence instructions
 
 //Example sequence one: Rainbow fade over 15 seconds: 
 fade(255,0,0,0,255,0,5000); //fade from red to green over 5 seconds
 fade(0,255,0,0,0,255,5000); //fade from green to blue over 5 seconds
 fade(0,0,255,255,0,0,5000); //fade from blue to red over 5 seconds
}

//function holds RGB values for time t milliseconds
void solid(int r, int g, int b, int t)
{

 //map values - arduino is sinking current, not sourcing it
 r = map(r, 0, 255, 255, 0);
 g = map(g, 0, 255, 255, 0);
 b = map(b, 0, 255, 255, 0); 

 //output
 analogWrite(rpin,r);
 analogWrite(gpin,g);
 analogWrite(bpin,b);
 
 //hold at this colour set for t ms
 delay(t);

}

//function fades between two RGB values over fade time period t
//maximum value of fade time = 30 seconds before gradient values
//get too small for floating point math to work? replace floats
//with doubles to remedy this?
void fade(int r1, int g1, int b1, int r2, int g2, int b2, int t)
{

 float r_float1, g_float1, b_float1;
 float r_float2, g_float2, b_float2;
 float grad_r, grad_g, grad_b;
 float output_r, output_g, output_b;
 
 //declare integer RGB values as float values
 r_float1 = (float) r1;
 g_float1 = (float) g1;
 b_float1 = (float) b1;
 r_float2 = (float) r2;
 g_float2 = (float) g2;
 b_float2 = (float) b2;
 
 //calculate rates of change of R, G, and B values
 grad_r = (r_float2-r_float1)/t;
 grad_g = (g_float2-g_float1)/t;
 grad_b = (b_float2-b_float1)/t;
 
 //loop round, incrementing time value "i"
 for ( float i=0; i<=t; i++ )
 {
   
   output_r = r_float1 + grad_r*i;
   output_g = g_float1 + grad_g*i;
   output_b = b_float1 + grad_b*i;
   
   //map values - arduino is sinking current, not sourcing it
   output_r = map (output_r,0,255,255,0);
   output_g = map (output_g,0,255,255,0);
   output_b = map (output_b,0,255,255,0);
   
   //output
   analogWrite(rpin, (int)output_r);
   analogWrite(gpin, (int)output_g);
   analogWrite(bpin, (int)output_b);
   
   //hold at this colour set for 1ms
   delay(1);
   
 }
}