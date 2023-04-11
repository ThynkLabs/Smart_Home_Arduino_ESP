#include "store.h"

struct board_status{
  bool board_ready=false;
  bool connection=false;
  bool mqtt_connection =false;
  bool wifi_connection=false;
}board_status;


extern void store_board_ready(bool status)
{
  board_status.board_ready=status;
}

extern bool store_get_board_ready_status()
{
  return board_status.board_ready;
}

void store_set_wifi_status(bool status)
{
  board_status.wifi_connection=status;
}

bool store_get_wifi_status()
{
  return board_status.wifi_connection;
}


void store_set_mqtt_status(bool status)
{
  board_status.mqtt_connection=status;
}

bool store_get_mqtt_status()
{
  return board_status.mqtt_connection;
}

void store_set_connection_status(bool status)
{
  board_status.connection=status;
}

bool store_get_connection_status()
{
  return board_status.connection;
}
