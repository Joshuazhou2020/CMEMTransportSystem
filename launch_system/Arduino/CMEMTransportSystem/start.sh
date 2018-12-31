echo "coil: $1 tag: $2 ver: $3"

tag=0
x=0
t=1000
y=0


# continue until $n equals 5
# tag, x, t, y, v, s, speed, efficiency

while read -r a b c d v s sd ef
do
if [[ "$a" < "$2" || "$a" == "$2" ]]  
then
 tag=$a
 x=$b
 t=$c
 y=$d
 echo "$a:$b:$c:$d"
 break
fi
done < model/model_$1

echo "$tag:$x:$t:$y"

mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/coil=\"[a-z]*[0-9]*\"/coil=\"$1\"/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/intervalXOn\=[0-9]*/intervalXOn=$x/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/intervalTOff\=[0-9]*/intervalTOff=$t/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/intervalYOff\=[0-9]*/intervalYOn=$y/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/ver\=[0-9]*/ver=$3/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino

/Applications/Arduino.app/Contents/MacOS/Arduino --upload /Users/wendy_shi/Documents/Arduino/CMEMTransportSystem/CMEMTransportSystem.ino
processing-java --sketch=/Users/wendy_shi/Documents/Processing/CMEMTransportSystem --run
