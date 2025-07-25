#include "exam.hpp"

void exam::fail_ex()
{
    std::string tmp = "bash .system/data_sender.sh \"fail_ex:" + current_ex->get_name() + " level:" + std::to_string(level) + " assignement:" + std::to_string(current_ex->get_assignement()) + "\"";
    system(tmp.c_str());
    current_ex->up_assignement();
    current_ex->set_time_bef_grade(time(NULL) + current_ex->grade_time() * 60);
    store_data();
}

void exam::success_ex(bool force)
{
    // insert current_ex in lvl_ex
    lvl_ex.insert(std::pair<int, exercise>(current_ex->get_lvl(), *current_ex));
    // insert the success exercise into file .system/exam_token/success_ex
    if (!force)
    {
        std::ofstream file;
        file.open("success/success_ex", std::ios::app);
        file << current_ex->get_name() << std::endl;
    }
    std::cout << std::endl
              << LIME << ">>>>>>>>>> SUCCESS <<<<<<<<<<" << RESET << std::endl
              << std::endl;
    std::string tmp;
    if (force)
        tmp = "bash .system/data_sender.sh \"cheat_success_ex: " + current_ex->get_name() + " level:" + std::to_string(level) + " assignment:" + std::to_string(current_ex->get_assignement()) + "\"";
    else
        tmp = "bash .system/data_sender.sh \"success_ex: " + current_ex->get_name() + " level:" + std::to_string(level) + " assignment:" + std::to_string(current_ex->get_assignement()) + "\"";
    system(tmp.c_str());
    up_lvl();
    std::cout << "(Press enter to continue...)" << std::endl;
    std::string input;
    if (!std::getline(std::cin, input))
        sigd();
    level_per_ex += level_per_ex_save;
    changex = 0;
    backup = 0;
    if (!force)
    {
        if (file_exists("rendu/"))
        {
            if (!file_exists("success"))
                system("mkdir success");
            system("cp -r rendu/* success/ 2> /dev/null");
        }
    }
    if (level_per_ex > 100)
        end_exam();
    start_new_ex();
}

void exam::end_exam()
{
    std::string tmp;
    remove(".system/exam_token/actuel_token.txt");
    if (using_cheatcode == 0)
    {
        if (student)
            tmp = "bash .system/data_sender.sh \"exam_success_end: examrank0" + std::to_string(exam_number) + "\"";
        else
            tmp = "bash .system/data_sender.sh \"exam_success_end: examweek0" + std::to_string(exam_number) + "\"";
        system(tmp.c_str());
        std::cout << WHITE << BOLD << "🥳 Congratulation! You have finished the Exam Rank 0" << exam_number << " !" << std::endl;
    }
    else
    {
        std::cout << WHITE << BOLD << "🙁 You have finished the Exam Rank 0" << exam_number << ", " << RED << BOLD << "after using " << using_cheatcode << " cheat command..." << WHITE << BOLD << std::endl;
        if (student)
            tmp = "bash .system/data_sender.sh \"exam_success_cheat" + std::to_string(using_cheatcode) + ": examrank0" + std::to_string(exam_number) + "\"";
        else
            tmp = "bash .system/data_sender.sh \"exam_success_cheat" + std::to_string(using_cheatcode) + ": examweek0" + std::to_string(exam_number) + "\"";
        system(tmp.c_str());
    }
    
    std::cout << "\n\e[1m\e[96mCongratulations on completing the exam!\e[0m\n" << std::endl;
    std::cout << "You have successfully finished ExamRank0" << exam_number << "!\n" << std::endl;
    
    std::cout << "What would you like to do next?\n" << std::endl;
    std::cout << "1. " << LIME << "Retry this exam" << RESET << " (start over with a clean slate)" << std::endl;
    std::cout << "2. " << YELLOW << "Try a different exam" << RESET << " (choose another ExamRank)" << std::endl;
    std::cout << "3. " << CYAN << "Support the project" << RESET << " (visit GitHub sponsor page)" << std::endl;
    std::cout << "4. " << RED << "Exit" << RESET << " (quit the program)" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter your choice (1-4): ";
    
    char choice;
    std::cin >> choice;
    
    switch(choice) {
        case '1':
        {
            std::cout << "\n" << LIME << "Restarting ExamRank0" << exam_number << "..." << RESET << std::endl;
            // Clean up files but keep exam settings
            system("rm -rf .system/exam_token/current_token.txt");
            system("rm -rf rendu subjects .system/grading traces success");
            sleep(2);
            system("clear");
            
            // Reset exam state to beginning
            level = 0;
            exam_grade = 0;
            failures = 0;
            using_cheatcode = 0;
            level_per_ex = ((double)level + 1) / (double)level_max * 100;
            level_per_ex_save = level_per_ex;
            
            // Restart with same exam settings
            std::cout << "You're connected " << LIME << username << RESET << "!" << std::endl;
            std::cout << "You can log out at any time. If this program tells you you earned points,\nthen they will be counted whatever happens.\n" << std::endl;
            std::cout << BOLD << WHITE << "You are about to start the project " << LIME << BOLD << "ExamRank0" << exam_number << BOLD << WHITE << ", in " << MAGENTA << "REAL" << BOLD << WHITE << " mode, at level " << YELLOW << level << BOLD << WHITE << "." << RESET << std::endl;
            std::cout << WHITE << BOLD << "You would have " << LIME << BOLD << (time_max / 60) << "hrs " << BOLD << WHITE << "to complete this project." << RESET << std::endl << "Press a key to start exam 🏁" << std::endl;
            std::string enter;
            if (!std::getline(std::cin, enter))
                sigd();
            
            // Reset timer
            start_time = time(0);
            end_time = start_time + (60 * time_max);
            
            start_new_ex();
            break;
        }
        case '2':
            std::cout << "\n" << YELLOW << "Starting exam selection..." << RESET << std::endl;
            // Clean up and go to exam selection
            system("rm -rf .system/exam_token/current_token.txt");
            system("rm -rf rendu subjects .system/grading traces success");
            sleep(2);
            system("clear");
            ask_param();
            start_new_ex();
            break;
            
        case '3': {
            std::cout << "\n" << CYAN << "Opening GitHub Sponsor page..." << RESET << std::endl;
            int is_linux = 0;
#ifdef __linux__
            is_linux = 1;
#endif
            if (is_linux)
                system("xdg-open https://github.com/sponsors/JCluzet");
            else
                system("open https://github.com/sponsors/JCluzet");
            std::cout << "\nThank you for considering supporting the project! 💝\n" << std::endl;
            std::cout << WHITE << BOLD << "Thanks for studying with us " << LIME << BOLD << username << WHITE << BOLD << " ❤️" << std::endl;
            exit(0);
            break;
        }
        case '4':
        default:
            std::cout << "\n" << WHITE << BOLD << "Thanks for studying with us " << LIME << BOLD << username << WHITE << BOLD << " ❤️" << std::endl;
            exit(0);
            break;
    }
}

// ==> GradeMe function call by entering `grademe` into prompt
void exam::grademe(void)
{
    if (file_exists(".system/grading/beta"))
    {
        std::cout << std::endl;
        std::cout << YELLOW << " ⚠️  Warning: " << RESET << "This exercise is a contribution by ";
        // output what is in .system/grading/beta
        std::ifstream file;
        file.open(".system/grading/beta");
        std::string line;
        std::getline(file, line);
        std::cout << YELLOW << line << RESET;
        std::cout << ", it's still in " << YELLOW << "beta testing" << RESET << "." << std::endl;
        std::cout << " If you want to add your contribution, visit the Github ReadME 👋" << std::endl;
        std::cout << " If you find any " << RED << "bug" << RESET << ", please report it on the Github repository." << std::endl;
    }

    std::cout << std::endl
              << "Before continuing, please make " << RED << "ABSOLUTELY SURE" << RESET << " that you are in the right directory," << std::endl;
    std::cout << "that you didn't forget anything, etc..." << std::endl;
    std::cout << "If your assignment is wrong, you will have the same assignment" << std::endl;
    std::cout << std::endl
              << " but with less potential points to earn !" << std::endl;
    std::cout << RED << "Are you sure?" << RESET << " [y/N] ";
    std::string input;
    if (!std::getline(std::cin, input))
        sigd();
    if (input == "y" || input == "Y")
    {
        if (current_ex->time_bef_grade > time(NULL) && waiting_time)
        {
            std::cout << RED << "ERROR: " << RESET << "You must wait at least " << YELLOW << BOLD;
            if ((((current_ex->time_bef_grade - time(NULL))) / 60) >= 1)
                std::cout << (current_ex->time_bef_grade - time(NULL)) / 60 << " minutes" << RESET << " and " << YELLOW << BOLD << (current_ex->time_bef_grade - time(NULL)) % 60 << " seconds" << RESET;
            else
                std::cout << (current_ex->time_bef_grade - time(NULL)) << " seconds" << RESET;
            std::cout << " until next grading request, so take your time to make more tests and be sure you will succeed next try!" << std::endl;
            return;
        }
        std::cout << "Ok, making grading request to server now." << std::endl;
        grade_request(0);
    }
    else
    {
        std::cout << " Abort" << std::endl;
    }
}

// ==> Function that call the bash grade system
void exam::grade_request(bool i)
{
    if (!i)
    {
        std::cout << std::endl
                  << "We will now wait for the job to complete." << std::endl
                  << "Please be " << LIME << "patient" << RESET << ", this " << LIME << "CAN" << RESET " take several minutes..." << std::endl;
        std::cout << "(10 seconds is fast, 30 seconds is expected, 3 minutes is a maximum)" << std::endl;
    }

    if (!file_exists(".system/grading/tester.sh"))
    {
        std::cout << "Error: Unable to find grading script for this exercise, it's coming soon. You can use \"force_success\" to pass this ex." << std::endl;
        return;
    }

    // Show test progress with simple messages
    std::cout << YELLOW << "TEST 1: Preparing grading environment..." << RESET << std::endl;
    usleep(500000);
    std::cout << YELLOW << "TEST 2: Compiling reference solution..." << RESET << std::endl;
    usleep(500000);
    std::cout << YELLOW << "TEST 3: Checking required files..." << RESET << std::endl;
    usleep(500000);
    std::cout << YELLOW << "TEST 4: Compiling student solution..." << RESET << std::endl;
    usleep(500000);
    std::cout << YELLOW << "TEST 5: Running output comparison tests..." << RESET << std::endl;
    usleep(500000);
    std::cout << YELLOW << "TEST 6: Finalizing results..." << RESET << std::endl;

    // Run the actual tester
    int result = system("bash .system/grading/tester.sh");

    // Debug: Check if tester ran
    if (result != 0)
    {
        std::cout << RED << "Tester script execution failed with code: " << result << RESET << std::endl;
    }

    if (file_exists(".system/grading/passed"))
    {
        success_ex(0);
    }
    else
    {
        std::cout << RED << ">>>>>>>>>> FAILURE <<<<<<<<<<" << RESET << std::endl;
        sleep(1);
        std::cout << "You have failed the assignment." << std::endl;

        // Debug: Check for traceback file existence
        if (file_exists("traceback"))
        {
            system("mkdir -p traces");
            std::string trace_name = std::to_string(level) + "-" + std::to_string(current_ex->get_assignement()) + "_" + current_ex->get_name() + ".trace";
            std::string cmd_system_call = "mv traceback traces/" + trace_name;
            system(cmd_system_call.c_str());
            std::cout << "Trace saved to " << LIME << current_path() << "/traces/" << trace_name << RESET << std::endl
                      << std::endl;
        }
        else
        {
            std::cout << "No traceback found." << std::endl;
            // Debug: Create a basic traceback
            system("mkdir -p traces");
            std::string trace_name = std::to_string(level) + "-" + std::to_string(current_ex->get_assignement()) + "_" + current_ex->get_name() + ".trace";
            std::ofstream debug_trace("traces/" + trace_name);
            debug_trace << "DEBUG: Tester script execution failed or no traceback generated\n";
            debug_trace << "Check if .system/grading/tester.sh exists and is executable\n";
            debug_trace << "Current exercise: " << current_ex->get_name() << "\n";
            debug_trace.close();
            std::cout << "Debug trace created at " << LIME << current_path() << "/traces/" << trace_name << RESET << std::endl
                      << std::endl;
        }
        fail_ex();
        std::cout << "(Press enter to continue...)" << std::endl;
        std::string input;
        if (!std::getline(std::cin, input))
            sigd();
        if (vip)
            infovip();
        else
            info();
    }
}
