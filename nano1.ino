#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
using namespace std;

int loopnumber = 0;
float temp[40];
int vibration[40];
int strain[40];

//suhu A4 (SDA) A5 (SCL)
//getaran A0
//berat D2 D3
//strain A1

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(115200);
	while (!Serial);

  if (!mlx.begin()) {
		Serial.println("Error connecting to MLX sensor. Check wiring.");
		while (1);
	};
}

void loop() {
	//Serial.print("Object = "); Serial.print(mlx.readObjectTempC()); Serial.print(" C"); Serial.println("");
  //Serial.print("Piezo = "); Serial.print(analogRead(0)); Serial.println("");
  //Serial.print("Scale = "); Serial.print(scale.get_units(10), 5); Serial.print(" g"); Serial.println("");
	
  /*
  {
    temperature: mlx.readObjectTempC(),
    vibration: analogRead(0),
    weight: scale.get_units(10),
    strain: analogRead(1)
  }
  */

  //Serial.println("[0," + String(temp, 2) + "," + String(analogRead(A0), DEC) + "," + String(analogRead(A1), DEC) + "]");
  if(loopnumber < 40) {
    temp[loopnumber] = mlx.readObjectTempC();
    vibration[loopnumber] = analogRead(A0);
    strain[loopnumber] = analogRead(A1);
    loopnumber++;
    //Serial.println(String(loopnumber));
  } else {
    float finaltemp = 0;
    int finalvibration = 0;
    int finalstrain = 0;
    for(int i = 0; i < 40; i++){
      finaltemp = max(finaltemp,temp[i]);
      finalvibration = max(finalvibration,vibration[i]);
      finalstrain = max(finalstrain,strain[i]);
    }

    Serial.println("[0," + String(finaltemp, 2) + "," + String(finalvibration, DEC) + "," + String(finalstrain, DEC) + "]");
    loopnumber = 0;
  }
  delay(25);
}