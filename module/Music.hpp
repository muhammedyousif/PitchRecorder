#include <iostream>
class Music{
    private:
        std::string note;
    public:
        Music(float hz);
        std::string MapHzToNotes(float hz);
};