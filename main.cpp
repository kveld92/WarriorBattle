#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

// std::to_string() doesn't work in MinGW, -bug
namespace patch{
    template < typename T > std::string to_string( const T& n ){
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}
class Warrior{
  private:
    std::string _name;
    int _maxHealth,
        _health,
        _attack,
        _defense,
        _agility;
  public:
    Warrior(std::string name, int health, int attack, int defense, int agility){
      this -> _name       = name;
      this -> _maxHealth  = health;
      this -> _health     = health;
      this -> _attack     = attack;
      this -> _defense    = defense;
      this -> _agility    = agility;
    }
    Warrior(){
      this -> _name       = "_testman";
      this -> _maxHealth  = 0;
      this -> _health     = 0;
      this -> _attack     = 0;
      this -> _defense    = 0;
      this -> _agility    = 0;
    }
    std::string getName(){ return this -> _name; }
    void setName(std::string name){ this -> _name = name; }

    int getMaxHealth(){ return this -> _maxHealth; }
    void setMaxHealth(int maxHealth){ this -> _maxHealth = maxHealth; }

    int getHealth(){ return this -> _health ; }
    void setHealth(int health){ this -> _health = health; }

    int getAttack(){ return this -> _attack; }
    void setAttack(int attack){ this -> _attack = attack; }

    int getDefense(){ return this -> _defense; }
    void setDefense(int defense){ this -> _defense = defense; }

    int getAgility(){ return this -> _agility; }
    void setAgility(int agility){ this -> _agility = agility; }

    int doAttack(){ return std::rand() % (this -> _attack + 1); }
    int doBlock(){ return std::rand() % (this -> _defense + 1); }
    bool doDodge(){ return std::rand() % 100 < this -> _agility ? true : false; }

    std::string toString(){
      return
        "HP: " + patch::to_string(this -> _maxHealth) +
        " ATT: " + patch::to_string(this -> _attack) +
        " DEF: " + patch::to_string(this -> _defense) +
        " AGI: " + patch::to_string(this -> _agility);
    }
};

class Battle{
  public:
    void simulateFight(Warrior warrior1, Warrior warrior2){
      int turn = 0;
      std::cout << "\n\t\t\t\tBATTLE!\n"
                << " ________________________________________________________________\n"
                << "|\t\t\t\t\t\t\t\t|\n"
                << "|\t" << warrior1.getName() << " (" << warrior1.toString() << ")\t\t|\n"
                << "| \t\t\t\tVS\t\t\t\t|\n"
                << "|\t" << warrior2.getName() << " (" << warrior2.toString() << ")\t\t|\n"
                << "|_______________________________________________________________|\n\n"
                << std::endl;

      while(warrior1.getHealth() > 0 && warrior2.getHealth() > 0){
        if(turn % 2 == 0){
          std::cout << warrior1.getName() << " " << healthBar(warrior1) << "\n" << std::endl;
          evaluateTurn(warrior1, warrior2);
        }
        else{
          std::cout << warrior2.getName() <<  " " << healthBar(warrior2) << "\n" << std::endl;
          evaluateTurn(warrior2, warrior1);
        }
        std::cout << "\n--------------------------------------------------------------------\n" << std::endl;
        turn++;
      }
      Warrior victor = evaluateVictor(warrior1, warrior2);
      std::cout << "_________________________________________________\n"
                << "|\t\t\t\t\t\t|\n"
                << "|\t" << victor.getName() << " won with " << victor.getHealth() << " HP left! \t\t| \n"
                << "|_______________________________________________|"
                << std::endl;
    }

    void evaluateTurn(Warrior& attacker, Warrior& blocker){
      const int attack        = attacker.doAttack(),
                block         = blocker.doBlock(),
                dodge         = blocker.doDodge(),
                damageDealt   = (attack - block) > 0 ? (attack - block) : 1;

      std::cout << "\t- Attempts to attack the enemy and racks up " << attack << " damage \n"
                << "\t- " << blocker.getName() << " heightens his defenses up to " << block << " points \n";
      if(!dodge) {
        blocker.setHealth(blocker.getHealth() - damageDealt);
        std::cout << "\t* "<< attacker.getName() << " dealt " << damageDealt << " damage to " << blocker.getName()  << " and has " << ""<< std::endl;
      }
      else std::cout << "\t^ "<< blocker.getName() << " dodged the attack!" << std::endl;
    }

    Warrior evaluateVictor(Warrior warrior1, Warrior warrior2){
      if(warrior1.getHealth() > warrior2.getHealth()) return warrior1;
      else return warrior2;
    }

    std::string healthBar(Warrior warrior){
      const std::string sMaxHealth = patch::to_string(warrior.getMaxHealth()),
                        sHealth    = patch::to_string(warrior.getHealth());
      return "(" + sHealth +"/" + sMaxHealth +" HP)";
    }
};

int main(){
  srand(time(NULL));
  Warrior batman("Batman", 110, 30, 15, 10);
  Warrior spiderman("Spiderman", 90, 25, 10, 20);
  Battle battle;
  battle.simulateFight(batman, spiderman);
  return 0;
}
