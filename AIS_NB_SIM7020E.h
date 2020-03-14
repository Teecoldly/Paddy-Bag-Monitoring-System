#ifndef AIS_NB_SIM7020E_h
#define AIS_NB_SIM7020E_h


#include <Arduino.h>
#include "AT_SIM7020E.h"


class AIS_NB_SIM7020E{
public:
	AIS_NB_SIM7020E();
	bool debug;
  bool tcp;
  bool udp;
	void (*Event_debug)(char *data);	

	void setupDevice(String serverdesport, String addressI);
  void setupDevice_fast();// not have set soket 
	String getDeviceIP();
	String getSignal();
	void pingIP(String IP);
	void powerSavingMode(unsigned int psm);
	bool checkPSMmode();
   void http_get(String ip,String page,String data_send);
	void sendMsgHEX(String address,String desport,String payload);
	void sendMsgSTR(String address,String desport,String payload,bool tcp);	
 
	void waitResponse(String &retdata,String server);
 
private:
	void send_msg(String address,String desport,unsigned int len,String payload);
	void send_msg_tcp(String address,String desport,unsigned int len,String payload);

protected:
	 Stream *_Serial;	
};

#endif
