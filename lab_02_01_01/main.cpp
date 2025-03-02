#include "menu/CMenu.h"
#include "menu/CMenuItem.h"

#include <ctime>
#include <cstdlib>


#pragma region функции-заглушки

int UserGreeting() {

    std::string user_name;

    std::cout << "Введите своё имя:\n";
    std::cin >> user_name;

    std::cout << "Привет, " << user_name << std::endl;

    return 1;
}

int UserPrediction() {

    srand(time(0));

    std::string predictions[] = {

        "Сегодня ты сделаешь что-то так классно, что все будут спрашивать: \"Как ты это сделал?\" Ты просто ответишь: \"Я же волшебник!",
        "У тебя не будет лишних 100 рублей, но будет 100 друзей и каждый из них подарит тебе по 100 рублей.", 
        "Не жди веселого предсказания. Будь реалистом — веселись сам.",
        "В этом году ты вырастешь на 10 сантиметров 一 купишь себе новые туфли.",
        "Перед тобой откроются все двери… супермаркетов.",
        "Если будешь просыпаться рано, ни разу не опоздаешь на работу.",
        "Год принесет существенную прибавку в весе 一 кошелек станет намного тяжелее.",
        "Твои мечты обретут невероятную силу и наконец-то объявят дивану бой.",
        "Если спрячешь ты заначку, найдешь попозже денег пачку."

    };

    std::cout << "Ваше предсказание:\n" << predictions[rand() % 3] << std::endl;
    return 2;

}

int RainAnimation() {

    int width_window = 20;
    int drops_count = 10;
    int duration_animation = 50;

    for (int i = 0 ; i < duration_animation; i++){

        system("clear");
        std::string sky(width_window,' ');

        for (int j = 0; j < drops_count; j++){

            sky[rand() % width_window] = "|";

        }

        std::cout << sky << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

    return 3;
}

#pragma endregion

const int ITEMS_NUMBER = 3;


int main() {
    CMenuItem items[ITEMS_NUMBER] {CMenuItem{"Приветствие", UserGreeting}, CMenuItem{"Предсказание", UserPrediction}, CMenuItem{"Посмотреть на дождик", RainAnimation}};
    CMenu menu("My console menu", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};
    return 0;
}