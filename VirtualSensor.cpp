//✅ 3 farklı sanal sensör (Sıcaklık, Nem, Basınç) rastgele veri üretecek.
//✅ Veriler belirli bir eşik değeri aştığında alarm verecek.
//✅ Veriler bir dosyaya kaydedilecek (data_log.txt).

#include <iostream>
#include <fstream> // Verileri dosyaya kaydetmek için
#include <cstdlib> // Rastgele sayı üretimi için
#include <ctime>
#include <thread>
#include <chrono> // Zaman gecikmeleri için

using namespace std;

class Sensor {
    public:
        string name;
        float minValue, maxValue;
        float threshold;

        //Constructor
        Sensor(string sensorName, float minV, float maxV, float thres)
            : name(sensorName), minValue(minV), maxValue(maxV), threshold(thres) {}

        //Random sayı üretme
        float generateData() {
            return minValue + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxValue - minValue)));
        }
};


//Veriyi dosyaya kaydetme fonksiyonu
void logData(const string &sensorName, float value) {
    ofstream file("data_log.txt", ios::app);
    if (file.is_open()) {
        file << sensorName << "Data: " << value << "\n";
        file.close();
    }
}


//Sensörlerin Çalışmasını Sağlayan Fonksiyon
void sensorSimulation(Sensor sensor, int interval) {
    while(true) {
        float data = sensor.generateData(); //Sensörden rastgele veri alırız
        cout << sensor.name << " Reading: " << data << "\n";
        logData(sensor.name, data); //Dosyaya kaydederiz
        if (data > sensor.threshold) {
            cout << "[ALERT]" << sensor.name << " value exceeded threshold!\n"; //Eşik değerinin üstündeyse uyarı mesajı göndeririz.
        }
        this_thread::sleep_for(chrono::seconds(interval)); // Belli aralıklarla bekler (örneğin 3 saniye, 5 saniye vs.)

    }
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    Sensor temperatureSensor("Temperature", 15.0, 40.0, 35.0);
    Sensor humiditySensor("Humidity", 30.0, 90.0, 80.0);
    Sensor pressureSensor("Pressure", 900.0, 1100.0, 1050.0);

    thread tempThread(sensorSimulation, temperatureSensor, 3); // Her sensörü ayrı thread (iş parçacığı) olarak çalıştırır
    thread humidityThread(sensorSimulation, humiditySensor, 5);
    thread pressureThread(sensorSimulation, pressureSensor, 7);

    tempThread.join();
    humidityThread.join();
    pressureThread.join();

    return 0;
}