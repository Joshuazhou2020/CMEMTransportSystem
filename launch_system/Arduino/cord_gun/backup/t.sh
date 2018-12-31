echo "On: $1"
echo "Off: $2"
echo "Ver: $3"
mv cord_gun_test.ino cord_gun_test.ino.in
sed  "s/intervalOn\=[0-9]*/intervalOn=$1/g" cord_gun_test.ino.in > cord_gun_test.ino

