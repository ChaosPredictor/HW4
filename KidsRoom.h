/*
 * KidsRoom.h
 *
 *  Created on: Jun 17, 2017
 *      Author: master
 */

#ifndef KIDSROOM_H_
#define KIDSROOM_H_


#include "EscapeRoomWrapper.h"

namespace mtm{
namespace escaperoom {

    class KidsRoom : public EscapeRoomWrapper {

    	int ageLimit;
    public:

    	KidsRoom(char* name, const int& escapeTime, const int& level, const int& maxParticipants, const int& ageLimit);

    	void setNewAgeLimit(const int& limit);

    	//void incNumberOfScaryEnigmas();

    	int getAgeLimit() const;

        //virtual int getRoomType() const;

        friend std::ostream& operator<<(std::ostream& output, const KidsRoom& room);

    };

    std::ostream& operator<<(std::ostream& output, const KidsRoom& room);

}
}


#endif /* KIDSROOM_H_ */
