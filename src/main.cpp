#include <Arduino.h>

int Merah = 23;
int Kuning = 22;
int Hijau = 21;

int Tombol1 = 34;
int Tombol2 = 35;
int Tombol3 = 32;

// Fungsi deklarasi
void kedipLampu(int lampu, int jumlah);
void kedipBergantian(int lampu1, int lampu2, int jumlah);
void kedipBerurutan(int jumlah);

void setup() {
    pinMode(Merah, OUTPUT);
    pinMode(Kuning, OUTPUT);
    pinMode(Hijau, OUTPUT);

    pinMode(Tombol1, INPUT_PULLUP);
    pinMode(Tombol2, INPUT_PULLUP);
    pinMode(Tombol3, INPUT_PULLUP);
}

void loop() {
    // Cek tombol 1
    if (digitalRead(Tombol1) == LOW) {
        delay(200); // Debounce
        while (digitalRead(Tombol1) == LOW); // Tunggu tombol dilepas
        kedipLampu(Merah, 5);
    } 
    
    // Cek tombol 2
    if (digitalRead(Tombol2) == LOW) {
        delay(200);
        while (digitalRead(Tombol2) == LOW);
        kedipBergantian(Merah, Hijau, 5);
    } 
    
    // Cek tombol 3
    if (digitalRead(Tombol3) == LOW) {
        delay(200);
        while (digitalRead(Tombol3) == LOW);
        kedipBerurutan(5);
    }
}

// Fungsi kedip untuk satu lampu
void kedipLampu(int lampu, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        digitalWrite(lampu, HIGH);
        delay(300);
        digitalWrite(lampu, LOW);
        delay(300);
    }
}

// Fungsi kedip bergantian untuk dua lampu
void kedipBergantian(int lampu1, int lampu2, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        digitalWrite(lampu1, HIGH);
        digitalWrite(lampu2, LOW);
        delay(300);
        digitalWrite(lampu1, LOW);
        digitalWrite(lampu2, HIGH);
        delay(300);
    }
    digitalWrite(lampu2, LOW);
}

// Fungsi kedip berurutan untuk tiga lampu
void kedipBerurutan(int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        digitalWrite(Merah, HIGH);
        delay(300);
        digitalWrite(Merah, LOW);

        digitalWrite(Kuning, HIGH);
        delay(300);
        digitalWrite(Kuning, LOW);

        digitalWrite(Hijau, HIGH);
        delay(300);
        digitalWrite(Hijau, LOW);
    }
}
