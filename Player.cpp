
class Player{

    Player::Player (Game* game , const std::string& name){
        this.game = game;
        this.name = name; 
    }


    std::string coup::getName const(){
        return this.name;
    }

    int coup::coins const(){
        return this.balance;
    }

    void coup::addCoins(int x){
        this.balance += x;
    }

    void coup::addCoins(int x){
        this.balance -= x;
    }

    bool coup::isInGame() const{
        return this.inGame;
    }

    void coup::lost(){
        this.inGame = false;
    }

    void startTurn(){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }
    }

    void coup::gather(){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }

        addCoins(1);
    }

    void coup::tax(){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }
        addCoins(2);
    }

    void coup::bribe(){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }
        if (this.coins() < 3) {
            throw std::runtime_error("Not enough coins to bribe.");
        }
    
        // לסיים
        
        subCoins(4);
        // לממש 2 תורים ברציופות        
    }

    void coup::arrest(Player& target){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }

        // If a merchant is attacked by a arrest, he Losing 2 coins instead of  pay 1 to the attacking player
        Merchant* merchant = dynamic_cast <Merchant*>(&target);
        if(merchant){
            target.AttackedByArrest();
            return;
        }
        else{    
            target.subCoins(1);
            this.addCoins(1);
            // לממש את זה שאסור לעשות את הפעולה על אותו שחקן 2 תורות רצוף (האם רצוף מאותו שחקן או מכול השחקנים ??) 
        }

        game.nextTurn();
    }

    void coup::sanction(Player& target){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }
        //השחקן בוחר שחקן אחר ומונע ממנו להשתמש בפעולות כלכליות (gather, tax) עד לתורו הבא. עלות פעולה זו היא 3 מטבעות.

        subCoins(3);
    }

    void coup::coup(Player& target){
        if (game.turn() != this.getName()) {
            throw std::runtime_error("It is not your turn");
        }

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