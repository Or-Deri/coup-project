
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
        target.subCoins(1);
        this.addCoins(1);
        // לממש את זה שאסור לעשות את הפעולה על אותו שחקן 2 תורות רצוף 
    }

    void coup::sanction(Player& target){
        //השחקן בוחר שחקן אחר ומונע ממנו להשתמש בפעולות כלכליות (gather, tax) עד לתורו הבא. עלות פעולה זו היא 3 מטבעות.

        subCoins(3);
    }

    void coup::coup(Player& target){
        subCoins(7);
        target.lost();
    }
    
}