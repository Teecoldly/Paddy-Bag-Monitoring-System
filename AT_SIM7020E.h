#include <Arduino.h>
#include <Stream.h>
struct tcpcoket{
  int CSOC;
  int port;
  String addr;
};
struct pingRESP{
	bool status;
	String addr;
	String ttl;
	String rtt;
};

struct signal{
	String csq;
	String rssi;
	String ber;
};

class AT_SIM7020E{
public:
	AT_SIM7020E();
	bool debug;
  bool tcp;
  bool udp;
  int numbersocket ;// tcp socket
	//--------- Parameter config ---------------
	const unsigned int msgLenMul=2;
	//=========Initialization Module=======
	void setupModule(String port,String address);
  void setupModule_fast();
	void check_module_ready();	
	void reboot_module();
	void pingIP(String IP);
	bool closeSocket();
	bool checkNetworkConnection();
	bool attachNetwork(String address,String port);
	void powerSavingMode(unsigned int psm);
 
  bool createTcpSocker(String address,String port);//tcp socket
  void opensoketcp(String address,String port);//tcp socket
  void opensokeudp(String address,String port);//tcp socket

  void http_post(String httpip,String page,String data_send);
  void http_close();
	//==========Get Parameter Value=========
	String getFirmwareVersion();
	String getIMEI();
	String getICCID();
	String getIMSI();
	String getDeviceIP();
	String getSignal();    
	String getAPN();
	String getNetworkStatus();
	bool checkPSMmode();
	//==========Data send/rec.===============
	void waitResponse(String &retdata,String server);
	void _Serial_print(String address,String port,unsigned int len);
	void _Serial_print(String input);
	void _Serial_print(unsigned int data);
	void _Serial_print(char*);
	void _Serial_println();
	//===============Utility=================
	void _serial_flush();	
    
private:
	//==============Buffer====================
	String data_input;
	String data_buffer;
	//==============Flag======================
	bool hw_connected=false;
	bool end=false;
	//==============Parameter=================
	unsigned int previous_check=0;
	//============Counter value===============
	byte k=0;
	//==============Function==================
	void echoOff();
	bool setPhoneFunction();
	void connectNetwork();
	bool createUDPSocket(String address,String port);
	void manageResponse(String &retdata,String server);
	bool enterPIN();
	void printHEX(char *str);

protected:
	Stream *_Serial;	
};
