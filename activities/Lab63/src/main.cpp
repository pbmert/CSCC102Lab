#include <iostream>
#include <optional>
#include <string>

void printSplashText() {
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "SBMR BUS TICKETING SERVICE" << endl;
    cout << "***  ***  ***" << endl;
    cout << "***  ***  ***" << endl;
    cout << "***  ***  ***" << endl;

    cout << "Bus Company" << endl;
    cout << "A - Victory Liner" << endl;
    cout << "  Destination" << endl;
    cout << "     1 - Baguio-800php" << endl;
    cout << "     2 - Pangasinan-750php" << endl;
    cout << "     3 - Sagada-1000php" << endl;
    
    cout << "B - Five Star Bus" << endl;
    cout << "  Destination" << endl;
    cout << "     1 - Liloan, Southern Leyte -2200php" << endl;
    cout << "     2 - Ormoc - 2090php" << endl;
    cout << "     3 - Tacloban-1850php" << endl;
    
    cout << "C - Philtranco" << endl;
    cout << "  Destination" << endl;
    cout << "     1 - Cagayan de Oro - 2200php" << endl;
    cout << "     2 - Davao - 2500php" << endl;
    cout << "     3 - Surigao - 1800php" << endl;
    
    cout << "Bus Class:" << endl;
    cout << "     O - Ordinary - No additional Fee" << endl;
    cout << "     R - Regular Airconditioned - Addition fee of 100 php each" << endl;
    cout << "     D - Deluxe - Additional fee of 200 php each" << endl;
    
    cout << "Trip Schedule:" << endl;
    cout << "     6 - 6 AM" << endl;
    cout << "     9 - 9 AM" << endl;
    cout << "     12 - 12 PM" << endl;
    
    cout << "---------------------" << endl;
    cout << "Booking Details:" << endl;
}

enum Bus {
    A,
    B,
    C,
};

std::optional<double> get_price_from_destination(Bus bus, std::string_view destination) {
    switch (bus) {
    case Bus::A:
        if (destination[0] == '1') {
            return 800.0;
        }
        else if (destination[0] == '2') {
            return 750.0;
        }
        else if (destination[0] == '3') {
            return 1000.0;
        }
        return {};
    case Bus::B:
        switch (destination) {
        case 1:
            return 2200.0;
        case 2:
            return 2090.0;
        case 3:
            return 1850.0;
        }
        return {};
    case Bus::C:
        switch (destination) {
        case 1:
            return 2200.0;
        case 2:
            return 2500.0;
        case 3:
            return 1800.0;
        }
        return {};
    default:
        std::cerr << "Unhandled bus type: " << bus << std::endl;
        std::exit(1);
    }
}

const char* bus_to_string(Bus &bus) {
    switch (bus) {
    case Bus::A:
        return "A";
    case Bus::B:
        return "B";
    case Bus::C:
        return "C";
    default:
        std::cerr << "Unhandled bus type: " << bus << std::endl;
        std::exit(1);
    }
}

std::optional<Bus> get_bus_from_input() {
    std::string input = "";
    std::cout << "Bus: ";
    std::getline(std::cin, input);
    
    switch (toupper(input[0])) {
    case 'A':
        return { Bus::A };
    case 'B':
        return { Bus::B };
    case 'C':
        return { Bus::C };
    default:
        std::cerr << "Bus " << input << " is not within our list of bus companies. Please try again." << std::endl;
        return {};
    }
}

enum BusClass {
    Ordinary,
    Regular,
    Deluxe,
};

std::optional<BusClass> get_bus_class_from_input() {
    std::string input = "";
    std::cout << "Bus Class: ";
    std::getline(std::cin, input);

    switch (input[0]) {
    // codechum bug
    case '0':
    case 'O':
        return { BusClass::Ordinary };
    case 'R':
        return { BusClass::Regular };
    case 'D':
        return { BusClass::Deluxe };
    default:
        std::cout << "We cannot find class for " << input[0] << ". Please try again." << std::endl;
        return {};
    }
}

double get_fee_from_bus_class(BusClass bus_class) {
    switch (bus_class) {
    case BusClass::Ordinary:
        return 0.0;
    case BusClass::Regular:
        return 100.0;
    case BusClass::Deluxe:
        return 200.0;
    default:
        std::cerr << "Unhandled bus class type: " << bus_class << std::endl;
        std::exit(1);
    }
}

double process_payment(double price) {
    std::cout << "Total Trip Bill: " << price << std::endl;
    std::cout << std::endl;

    double payment = 0.0;
    for (;;) {
        std::cout << "Payment: ";
        std::cin >> payment;

        if (payment >= price) break;
        std::cout << "Invalid payment, please input the right amount" << std::endl;
    }

    return payment - price;
}

void iterate() {
    printSplashText();

    auto bus = get_bus_from_input();
    if (!bus.has_value()) return;

    double ticket_price = 0.0;
    {
        std::string destination = "";
        std::cout << "Destination: ";
        std::getline(std::cin, destination);
        
        if (auto raw_price = get_price_from_destination(*bus, destination); raw_price) {
            ticket_price = *raw_price;
        } else {
            std::cerr << "Invalid destination for Bus" << bus_to_string(*bus) << ". Please try again." << std::endl;
            return;
        }
    }

    auto bus_class = get_bus_class_from_input();
    if (!bus_class.has_value()) return;

    double fees = get_fee_from_bus_class(*bus_class);
    std::string month = "";
    int num_of_tickets = 0;
    int day, year, trip_schedule = 0;

    std::cout << "Number of Tickets: ";
    std::cin >> num_of_tickets;
    std::cout << "Month:";
    std::cin >> month;
    std::cout << "Date:";
    std::cin >> day;
    std::cout << "Year:";
    std::cin >> year;
    std::cout << "Trip Schedule:";
    std::cin >> trip_schedule;

    if (trip_schedule != 6 && trip_schedule != 9 && trip_schedule != 12) {
        std::cerr << "Schedule for " << trip_schedule << " is not available. Please try again." << std::endl;
        return;
    }

    // multiply fees and ticketBills by number of tickets
    double ticket_bills = ticket_price * num_of_tickets;
    fees *= num_of_tickets;

    std::cout << std::endl;
    std::cout << "Thank you for booking with us!" << std::endl;
    std::cout << "Have a safe trip!" << std::endl << std::endl;

    double total_trip_bill = ticket_bills + fees;
    process_payment(total_trip_bill);
}

bool prompt_continue_question() {
    for (;;) {
        std::string answer_str = " ";
        std::cout << "Do you want to create another booking? [yes/no]";
        std::getline(std::cin, answer_str);

        char answer = toupper(answer_str[0]);
        if (answer == 'Y') {
            return true;
        } else if (answer == 'N') {
            return false;
        }
    }
}

int main() {
    for (;;) {
        iterate();
        bool should_continue = prompt_continue_question();
        if (!should_continue) break;
    }
    std::cout << "Application terminated..." << std::endl;
	return 0;
}
