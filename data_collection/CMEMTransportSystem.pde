import processing.serial.*;
Serial mySerial;
PrintWriter output;
String filename;
boolean created=false;
void setup() {
size(400, 400);
mySerial = new Serial( this, Serial.list()[1], 9600 );
filename = "";
output = createWriter( "data.txt" );
}
void draw() {
      
if (mySerial.available() > 0 ) {
String value = mySerial.readString();

if ( value != null ) 
{
print(value);
if (value.contains("_"))
{
  filename= filename + value;
  //println("1" + filename);
} else if (!filename.equals("") && !filename.contains("txt"))
{
  //println("2" + filename);
  filename= filename + value;
}
else if (filename.contains("txt") && !created)
{
  filename = filename.trim();
  filename = filename.replace("?", "");
  output = createWriter("data/"+filename);
  created = true;
}
else {
    output.print( value );
}
}
}
}
void keyPressed() {
output.flush(); // Writes the remaining data to the file
output.close(); // Finishes the file
exit(); // Stops the program
}
