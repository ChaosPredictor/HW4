/*
 * ScaryRoom.h
 *
 *  Created on: Jun 17, 2017
 *      Author: master
 */

#ifndef SCARYROOM_H_
#define SCARYROOM_H_

#include "EscapeRoomWrapper.h"

namespace mtm{
namespace escaperoom {

    class ScaryRoom : public EscapeRoomWrapper {

    	int ageLimit;
    	int numOfScaryEnigmas;
    public:
    	ScaryRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit, const int& numOfScaryEnigmas);

    	void setNewAgeLimit(const int& limit);

    	void incNumberOfScaryEnigmas();

    	int getAgeLimit() const;

        friend std::ostream& operator<<(std::ostream& output, const ScaryRoom& room);

    };

    std::ostream& operator<<(std::ostream& output, const ScaryRoom& room);

}
}



#endif /* SCARYROOM_H_ */
