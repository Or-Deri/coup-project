
class Player{
    



    std::string getName const(){
        return this.name;
    }

    int getCoins const(){
        return this.coins;
    }

    void addCoins(int x){
        this.coins += x;
    }

    void addCoins(int x){
        this.coins -= x;
    }

    bool isInGame const(){
        return this.inGame;
    }

    void lost(){
        this.inGame = false;
    }

    
}