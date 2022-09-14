#include "Block.h"
#include "Hash.h"

std::string mineHash(std::string str){
    str.at(0) = str.at(0) + 1;

    while (!validate_hash(Hash::PRH24(str))){
        str = std::to_string(Hash::PRH24(str));
    }

    return str;
}

int main(){
    std::string transaction;
    getline(std::cin, transaction);
    
    Block* prev = nullptr;
    Block* latestBlock = nullptr;
    std::string prevNum = "2";

    while (!transaction.empty()){


        latestBlock = new Block(transaction, prev);

        while (!latestBlock->sign_block(prevNum)){
            prevNum = mineHash(prevNum);
            latestBlock->sign_block(prevNum);
        }

        prev = latestBlock;

        transaction.clear();
        getline(std::cin, transaction);
    }
    while (latestBlock){
        std::cout << *latestBlock;
        prev = latestBlock->get_prev();
        delete latestBlock;
        latestBlock = prev;
    }
}