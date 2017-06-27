// float r=sqrt(1750/(12*M_PI)); // Hpir^2=1750 = sqrt(1750/(Hpi))=r
const float Vmax = 4.76, Vmin = 0.07, Dmax = 9, Dmin = 0, M = (Vmax-Vmin)/(Dmax-Dmin), H=13.5; // ALTURA A 2.250 LITROS! (MAXIMA)
float voltage, Vprom, d, Vol, r, m = (2250-680)/(H-4);
String str1 = "Voltaje: ", str2 = "Voltaje Prom: ", str3 = "Volumen: ", str4 = " Litros";

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  delay(1);
  voltage = analogRead(0) * 5.0 / 1023.0;
  //Serial.println(str1 + voltage);
  readV(100);
  //Serial.println(str2 + Vprom);//VOLTAJE PROMEDIO
  //*** d = (Vprom - Vmax) / ((Vmax - Vmin) / (Dmax - Dmin));  ***   //FUNCION PENDIENTE ORDENADA AL ORIGEN  PARA CALCULAR DISTANCIA RESPECTO AL VOLTAJE
  //*** d = Vprom * 15 / Vmax   // REGLA DE TRES!!
  d = (Vmax - Vprom) / ((Vmax - Vmin) / (Dmax - Dmin)) + 1;
  //D_rangoV();
  //calcR();
  
  //Vol=(H-d)*M_PI*pow(r,2);// CENTIMETROS CUBICOS
  Vol = (m * (H-d)) + C();  // SUMAR 88.1578  (volumen de hasta abajo!!)
  Serial.println(str3 + Vol/1000 + str4); //Vol/1000  = LITROS        Vol = cm cubicos
  Serial.println("\n");
  delay(5000);
}

float readV(int times){
  float PromValores;
  for(int x=0;x<times;x++){  // calcula el promedio basado en el numero de "precicion"
    delay(1);
    PromValores+=analogRead(0);
  }
  //Serial.println(PromValores);
  Vprom = (PromValores/times) * 5.0 / 1023.0;// return (PromValores/times);
}

//*** d = Vprom - Vmax) / ((Vmax - Vmin) / (Dmax - Dmin));  ***
// SUMAR LA DISTANCIA DE LOS SENSORES A 12cm DEL FONDO!!!**** (d + distanciaSENSORES a 12cm)
int D_rangoV(){
  if(Vprom>=4.5){
    d = (4.76-Vprom) / ((4.76 - 4.5) / (1 - 0.01));   //FUNCION PENDIENTE ORDENADA AL ORIGEN  PARA CALCULAR DISTANCIA RESPECTO AL VOLTAJE
  }
  else if(Vprom<4.5 && Vprom>=3){
    d = (4.3-Vprom) / ((4.5 -3) / (5-1));
  }
  else if(Vprom<3 && Vprom>=1){
    d = (3-Vprom) / ((3-1) / (10-5));
  }
  else{
    d = (1-Vprom) / ((1 - 0.1) / (15-10)); 
  }
}


//**** CALCULAR VOLUMEN CON PENDIENTE DE ALTURA Y VALORES DE VOLUMEN!!!!*******
// Vol = m * (H-d);
float C(){
  float c;
  if(H-d>11){
    c=18.9473;
  }
  else if(H-d<=11 && H-d>9){
    c=139.2106;
  }
  else if(H-d<=9 && H-d>5){
    c=88.1578;
  }
  else{
    c=18.9473;
  }
  return c;
}

