//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_MYARDUINOPROPERTY_MYSENSORSPROPERTY_H
#define COM_LILICLOUD_MYARDUINOPROPERTY_MYSENSORSPROPERTY_H

#include <Property.h>
#include <MySensors.h>

template<typename T>
class MySensorsProperty : public Property<T> {
protected:
    /**
     * MyMessage object to send or receive data to or from gateway
     */
    MyMessage * message;

    /**
     * Child sensor id
     */
    byte childId;

public:
    /**
     * Constructor
     * 
     * @param byte childId Sensor id
     * @param mysensors_data_t dataType Date type
     */
    MySensorsProperty(byte childId, const mysensors_data_t dataType) : Property<T>()
    {
        this->construct(childId, dataType);
    }

    /**
     * Constructor
     * 
     * @param byte childId Sensor id
     * @param mysensors_data_t dataType Date type
     * @param T initValue Init value to affect on init
     */
    MySensorsProperty(byte childId, const mysensors_data_t dataType, T initValue) : Property<T>(initValue)
    {
        this->construct(childId, dataType);
    }

    /**
     * Destructor
     */
    virtual ~MySensorsProperty()
    {
        delete this->message;
    }

    /**
     * Common method for constructor
     * 
     * @param byte childId Sensor id
     * @param mysensors_data_t dataType Date type
     * @param T initValue Init value to affect on init
     */
    void construct(byte childId, const mysensors_data_t dataType)
    {
        this->childId = childId;
        this->message = new MyMessage(childId, dataType);        
    }

    /**
     * Get MyMessage object
     */
    MyMessage * getMessage()
    {
        return this->message;
    }
    
    /**
     * Get child id
     */
    byte getChildId()
    {
        return this->childId;
    }

    /**
     * Set value
     */
    virtual T set(T value)
    {  
        return this->set(value, true);
    }
    
    /**
     * Set value
     */
    virtual T set(T value, bool sendToGateway) {
        // Parent
        T v = Property<T>::set(value);

        // Send to gateway
        if (sendToGateway) {
            send(this->message->set(v));
        }

        return v;
    }
};

#endif //COM_LILICLOUD_MYARDUINOPROPERTY_MYSENSORSPROPERTY_H
