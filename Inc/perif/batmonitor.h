#pragma once

#ifndef PERIF_BATMONITOR_H_
#define PERIF_BATMONITOR_H_

#include "cmain.h"

namespace quad
{
class BatMonitor
{
public:
float_t getBatteryVoltage();
};
}

#endif /* PERIF_BATMONITOR_H_ */
