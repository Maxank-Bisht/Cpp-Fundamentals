﻿#include <future>
#include <iostream>

struct DatabaseConnection {};

void updateOrderList(DatabaseConnection&) {
    std::cout << "Updating order list" << std::endl;
}

void scheduleOrderProcessing(DatabaseConnection&) {
    std::cout << "Schedule order processing" << std::endl;
}

/* We need to get a copy of the shared_ptr so it stays alive until this
function finishes */
void updateWithConnection(std::shared_ptr<DatabaseConnection> connection) {
    updateOrderList(*connection);
}

/* We need to get a copy of the shared_ptr so it stays alive until this
function finishes. */
void scheduleWithConnection(std::shared_ptr<DatabaseConnection> connection) {
    scheduleOrderProcessing(*connection);
}

int main()
{
    std::shared_ptr<DatabaseConnection> connection = std::make_shared<DatabaseConnection>();
    std::cout << "Updating order and scheduling order processing in parallel" << std::endl;
    auto updateResult = std::async(std::launch::async, updateWithConnection, connection);
    auto scheduleResult = std::async(std::launch::async, scheduleWithConnection, connection);

    updateResult.wait();
    scheduleResult.wait();
}
