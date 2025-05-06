
class Player{

    Player::Player (Game* game , const std::string& name){
        this.game = game;
        this.name = name; 
    }


    std::string coup::getName const(){
        return this.name;
    }

    int coup::getCoins const(){
        return this.coins;
    }

    void coup::addCoins(int x){
        this.coins += x;
    }

    void coup::addCoins(int x){
        this.coins -= x;
    }

    bool coup::isInGame const(){
        return this.inGame;
    }

    void coup::lost(){
        this.inGame = false;
    }

    void startTurn(){}

    void coup::gather(){

        addCoins(1);
    }

    void coup::tax(){

        addCoins(2);
    }

    void coup::bribe(){
        subCoins(4);
        // לממש 2 תורים ברציופות        
    }

    void coup::arrest(Player& target){

        // If a merchant is attacked by a arrest, he Losing 2 coins instead of  pay 1 to the attacking player
        Merchant* merchant = dynamic_cast <Merchant*>(&target);
        if(merchant){
            target.AttackedByArrest();
            return;
        }

        target.subCoins(1);
        this.addCoins(1);
        // לממש את זה שאסור לעשות את הפעולה על אותו שחקן 2 תורות רצוף 
    }

    void coup::sanction(Player& target){
        //השחקן בוחר שחקן אחר ומונע ממנו להשתמש בפעולות כלכליות (gather, tax) עד לתורו הבא. עלות פעולה זו היא 3 מטבעות.

        subCoins(3);
    }

    void coup::coup(Player& target){

        General* general = dynamic_cast <General*>(&target);
        if(general){// גנרל יכול לבטל את הפעולה
            
            if (general->isCoupUndo()){
                target->setUndo(false);
                // ממשיך לתור הבא 
                return;
            }
        }

        subCoins(7);
        target.lost();
    }
    
}