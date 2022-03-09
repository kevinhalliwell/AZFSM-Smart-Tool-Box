void setup() {
  // put your setup code here, to run once:
system("/etc/init.d/networking restart");
}

void loop() {
  // put your main code here, to run repeatedly: 
  system("ifconfig > /dev/ttyGS0");
  sleep(10);
}
