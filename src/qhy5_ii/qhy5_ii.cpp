#include "qhy5_ii.h"
#include "qhyccd.h"
#include "common.h"


struct camdata {
    int w;
    int h;
    int bpp; //bit depth
    int bin; //binmode default 1x1
    int channels;
    int gain;
    int exptime;
    unsigned char *pixels;
} cam;

struct {
    int count;
    int status;
    int write;
    int quit;
} stat;


qhyccd_device_handle *device_handle;
qhyccd_device *device;

extern "C" {
    pcl::QHY5_ii_Camera* InitializeDevice(void) {
        cam.w=1280;
        cam.h=960;
        cam.bpp=8;
        cam.channels=1;
        cam.gain = 1000;
        cam.pixels = (unsigned char *)malloc(cam.w*cam.h*(cam.bpp/2));
        return new pcl::QHY5_ii_Camera();
    }
}

namespace pcl
{

    QHY5_ii_Camera::QHY5_ii_Camera():cameraType(TypeCCD)
    {
    }

    void QHY5_ii_Camera::Dispose()
    {
    }

    void QHY5_ii_Camera::SetLogger(void(*_theLogger)(String))
    {
        theLogger = _theLogger;
        theLogger(String("The Logger has been successfully set."));
    }

    short QHY5_ii_Camera::BinX()
    {
        return -1;
    }

    short QHY5_ii_Camera::BinY()
    {
        return -1;
    }

    int QHY5_ii_Camera::SetBinX(short binX)
    {
        return -1;
    }

    int QHY5_ii_Camera::SetBinY(short binY)
    {
        return -1;
    }

    IPixInsightCamera::CameraStateEnum QHY5_ii_Camera::CameraState()
    {
        return CameraError;
    }

    long QHY5_ii_Camera::CameraXSize()
    {
        return -1;
    }

    long QHY5_ii_Camera::CameraYSize()
    {
        return -1;
    }

    bool QHY5_ii_Camera::CanAbortExposure()
    {
        return true;
    }

    bool QHY5_ii_Camera::CanAsymmetricBin()
    {
        return false;
    }

    bool QHY5_ii_Camera::CanGetCoolerPower()
    {
        return false;
    }

    bool QHY5_ii_Camera::CanPulseGuide()
    {
        return true;
    }

    bool QHY5_ii_Camera::CanSetCCDTemperature()
    {
        return false;
    }

    bool QHY5_ii_Camera::CanStopExposure()
    {
        return true;
    }

    double QHY5_ii_Camera::CCDTemperature()
    {
        return -1;
    }

    bool QHY5_ii_Camera::Connected()
    {
        return false;
    }

    int QHY5_ii_Camera::ConnectCamera()
    {
        return -1;
    }

    int QHY5_ii_Camera::DisconnectCamera()
    {
        CloseCamera();
        return -1;
    }

    int QHY5_ii_Camera::SetConnected(bool connectCamera)
    {
        if(connectCamera) {
            stat.status = OpenCameraByID(DEVICETYPE_QHY5LII);

            if(stat.status == 0) {
                throw Error("No camera found - please connect camera and try again");
            }
            SetTransferBit(cam.bpp);

            SetGain(cam.gain);

            SetSpeed(false);
            SetUSBTraffic(255);//0-255 increase the value will reduce the speed.
            BeginLive();
        } else {
            CloseCamera();
        }

        return 1;
    }

    bool QHY5_ii_Camera::CoolerOn()
    {
        return false;
    }

    int QHY5_ii_Camera::SetCoolerOn(bool coolerOn)
    {
        return 0;
    }
    double QHY5_ii_Camera::CoolerPower()
    {
        return 0;
    }

    String QHY5_ii_Camera::Description()
    {
        return String("QHY5L-ii");
    }

    double QHY5_ii_Camera::ElectronsPerADU()
    {
        return 1;
    }

    double QHY5_ii_Camera::FullWellCapacity()
    {
        return 1;
    }

    bool QHY5_ii_Camera::HasShutter()
    {
        false;
    }

    double QHY5_ii_Camera::HeatSinkTemperature()
    {
        return 1;
    }

    // uint16 QHY5_ii_Camera::ASCOMDataToPi( long _i )
    // {
    //     return _i + 32768;
    // }

    //Application needs to own this memory...
    //This may need to be a pointer instead...
    void QHY5_ii_Camera::ImageArray(UInt16Image *theImage)
    {
        uint8 *imageData = cam.pixels;
        //unsigned char* pixels = cam.pixels;
        uint16 *piImageData = **theImage;
        for( size_type i = 0, N = theImage->NumberOfPixels(); i < N; ++i)
            *piImageData++ = (*imageData++)*255;
    }

    bool QHY5_ii_Camera::ImageReady()
    {
        true;
    }

    bool QHY5_ii_Camera::IsPulseGuiding()
    {
        false;
    }

    String QHY5_ii_Camera::LastError()
    {
        return String("");
    }
    double QHY5_ii_Camera::LastExposureDuration()
    {
        return 1;
    }
    // Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format.
    String QHY5_ii_Camera::LastExposureStartTime()
    {
        return String("");
    }

    long QHY5_ii_Camera::MaxADU()
    {
        return 1;
    }

    short QHY5_ii_Camera::MaxBinX()
    {
        return -1;
    }

    short QHY5_ii_Camera::MaxBinY()
    {
        return -1;
    }

    long QHY5_ii_Camera::NumX()
    {
        return cam.w;
    }

    long QHY5_ii_Camera::NumY()
    {
        return cam.h;
    }

    int QHY5_ii_Camera::SetNumX(long numX)
    {
        return -1;
    }

    int QHY5_ii_Camera::SetNumY(long numY)
    {
        return -1;
    }

    double QHY5_ii_Camera::PixelSizeX()
    {

        return -1;
    }

    double QHY5_ii_Camera::PixelSizeY()
    {
        return -1;
    }

    int QHY5_ii_Camera::SetCCDTemperature(double ccdTemp)
    {
        return -1;
    }

    double QHY5_ii_Camera::GetSetCCDTemperature()
    {
        return -1;
    }

    long QHY5_ii_Camera::StartX()
    {
        return -1;
    }

    int QHY5_ii_Camera::SetStartX(long setX)
    {
        return -1;
    }

    long QHY5_ii_Camera::StartY()
    {
        return -1;
    }

    int QHY5_ii_Camera::SetStartY(long setY)
    {
        return -1;
    }

    int QHY5_ii_Camera::AbortExposure()
    {
        return 0;
    }

    int QHY5_ii_Camera::PulseGuide(IPixInsightCamera::GuideDirection direction, long duration)
    {
        return -1;
    }

    void QHY5_ii_Camera::SetupDialog()
    {
    }

    void QHY5_ii_Camera::StartExposure(double duration)
    {
        SetExposeTime(duration * 1000);
        GetImageData(cam.w, cam.h, cam.bpp, cam.channels, cam.pixels);
    }

    void QHY5_ii_Camera::StopExposure()
    {
    }
}
