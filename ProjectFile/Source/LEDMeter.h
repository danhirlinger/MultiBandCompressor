#pragma once

//namespace Blackway
//{
    class LEDMeter : public Component,
                     private Timer
    {
    public:
    //    enum MeterType
    //    {
    //        Vertical,
    //        Horizontal,
    //    };

        LEDMeter(
            std::atomic<float>& sourceValue
        ) : source(sourceValue)
        {
            startTimerHz(30);
        }

        ~LEDMeter() = default;

    private:
        void timerCallback() override
        {
            const float newValue = source.load();

            // Because our meter is divided up we can drastically limit how often
            // we need to repaint
            if (fabsf(newValue - prevValue) >= 0.001f)
            {
                prevValue = newValue;
                repaint();
            }
        }

        void enablementChanged() override
        {
            if (isEnabled())
            {
                startTimerHz(30);
            }
            else
            {
                stopTimer();
                repaint();
            }
        }

        void paint(Graphics& g) override
        {

            const float tempValue = (isEnabled()) ? prevValue : 0.0f;
            const float value = jlimit(0.0f,1.0f,tempValue);
            
            const int nFrames = 37;
            //const int ledWidth = 46;
            const int ledHeight = 418;
            
            Image ledMeter;
            
            ledMeter = ImageCache::getFromMemory (BinaryData::meter_37_frms_png, BinaryData::meter_37_frms_pngSize);
            
            const int frameIdx = (int)ceil(value * ((double)nFrames-1.0) );

            g.drawImage( ledMeter,
                        (int)0, (int)0, getWidth(), getHeight(),   // dest
                        0, frameIdx*ledHeight, ledMeter.getWidth(), ledHeight); // source
            
        }

        std::atomic<float>& source;
        float prevValue = 0.0f;
        //const MeterType type;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LEDMeter)
    };


//}
