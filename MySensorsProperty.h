//
// Created by Thibault PLET on 22/10/2023.
//

#ifndef COM_LILICLOUD_MYARDUINOPROPERTY_MYSENSORSPROPERTY_H
#define COM_LILICLOUD_MYARDUINOPROPERTY_MYSENSORSPROPERTY_H

#include <Property.h>
#include <MySensors.h>

template<typename T>
class MySensorProperty : public Property<T> {
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
    MySensorProperty(byte childId, const mysensors_data_t dataType) : Property<T>()
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
    MySensorProperty(byte childId, const mysensors_data_t dataType, T initValue) : Property<T>(initValue)
    {
        this->construct(childId, dataType);
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
        this->message = new MyMessage(childId)        
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
    T set(T value)
    {  
        this->set(value, true);
    }
    
    /**
     * Set value
     */
    T set(T value, bool sendToGateway) {
        // Parent
        Property<T>::set(value);

        // Send to gateway
        if (sendToGateway) {
            send(this->message->set(this->get()));
        }

        return this->value;
    }
};

#endif //COM_LILICLOUD_MYARDUINOPROPERTY_MYSENSORSPROPERTY_H
