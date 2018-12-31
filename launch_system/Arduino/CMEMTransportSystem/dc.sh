echo "Coil: $1"
echo "X On: $2"
echo "T Off: $3"
echo "Y On: $4"
echo "Ver: $5"

mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/coil=\"[a-z]*[0-9]*\_*[a-z]*\"/coil=\"$1\"/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/intervalXOn\=[0-9]*/intervalXOn=$2/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/intervalTOff\=[0-9]*/intervalTOff=$3/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/intervalYOn\=[0-9]*/intervalYOn=$4/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino
mv CMEMTransportSystem.ino CMEMTransportSystem.ino.in
sed  "s/ver\=[0-9]*/ver=$5/g" CMEMTransportSystem.ino.in > CMEMTransportSystem.ino

/Applications/Arduino.app/Contents/MacOS/Arduino --upload /Users/wendy_shi/Documents/Arduino/CMEMTransportSystem/CMEMTransportSystem.ino
processing-java --sketch=/Users/wendy_shi/Documents/Processing/CMEMTransportSystem --run


