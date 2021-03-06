#pragma once
#include "ProtobufPlugin.h"
#include "../mesh/generated/environmental_measurement.pb.h"
#include <OLEDDisplay.h>
#include <OLEDDisplayUi.h>


class EnvironmentalMeasurementPlugin : private concurrency::OSThread
{
    bool firstTime = 1;

  public:
    EnvironmentalMeasurementPlugin();

  protected:
    virtual int32_t runOnce();
};

extern EnvironmentalMeasurementPlugin *environmentalMeasurementPlugin;

/**
 * EnvironmentalMeasurementPluginRadio plugin for sending/receiving environmental measurements to/from the mesh
 */
class EnvironmentalMeasurementPluginRadio : public ProtobufPlugin<EnvironmentalMeasurement>
{
  public:
    /** Constructor
     * name is for debugging output
     */
    EnvironmentalMeasurementPluginRadio() : ProtobufPlugin("EnvironmentalMeasurement", PortNum_ENVIRONMENTAL_MEASUREMENT_APP, &EnvironmentalMeasurement_msg) {
      lastMeasurement.barometric_pressure = nanf("");
      lastMeasurement.relative_humidity =  nanf("");
      lastMeasurement.temperature =  nanf("");
      lastSender = "N/A";
    }

    /**
     * Send our EnvironmentalMeasurement into the mesh
     */
    bool sendOurEnvironmentalMeasurement(NodeNum dest = NODENUM_BROADCAST, bool wantReplies = false);
    
    virtual void drawFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);

  protected:
    
    /** Called to handle a particular incoming message

    @return true if you've guaranteed you've handled this message and no other handlers should be considered for it
    */
    virtual bool handleReceivedProtobuf(const MeshPacket &mp, const EnvironmentalMeasurement &p);

    virtual bool wantUIFrame();


  private:
  
    EnvironmentalMeasurement lastMeasurement;

    String lastSender;

};

extern EnvironmentalMeasurementPluginRadio *environmentalMeasurementPluginRadio;