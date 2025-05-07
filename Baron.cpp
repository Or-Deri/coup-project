#include "Baron.hpp"
#include "Game.hpp"
#include <stdexcept>


namespace coup {

    Baron::Baron(Game& game, const std::string& name){
        this.game = game;
        this.name = name;
    }



    void invest(){
        // יכול "להשקיע" 3 מטבעות ולקבל בתמורה 6 מטבעות. בנוסף, אם הוא מותקף באמצעות חרם (sanction), הוא מקבל מטבע אחד כפיצוי (כלומר, מכל התהליך הוא יכול להפסיד לכל היותר מטבע אחד אם השתמש במס)
        if (this.getCoins < 3){
            throw runtime_error ("Not enough coins");
        }

        subCoins(3);
        //  כאן בודק אם מישהו מערער 
        // מוסיף לו 6  אם לא

    }




}