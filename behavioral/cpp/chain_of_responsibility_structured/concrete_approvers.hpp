#pragma once
#include "interfaces.hpp"

class TeamLead : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount <= 1000) {
            std::cout << "TeamLead: Approved request of $" << amount << std::endl;
        } else if (nextApprover) {
            std::cout << "TeamLead: Amount exceeds limit, passing to manager..." << std::endl;
            nextApprover->approveRequest(amount);
        } else {
            std::cout << "TeamLead: Cannot approve this amount" << std::endl;
        }
    }
};

class ManagerApprover : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount <= 5000) {
            std::cout << "Manager: Approved request of $" << amount << std::endl;
        } else if (nextApprover) {
            std::cout << "Manager: Amount exceeds limit, passing to director..." << std::endl;
            nextApprover->approveRequest(amount);
        } else {
            std::cout << "Manager: Cannot approve this amount" << std::endl;
        }
    }
};

class Director : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount <= 20000) {
            std::cout << "Director: Approved request of $" << amount << std::endl;
        } else if (nextApprover) {
            std::cout << "Director: Amount exceeds limit, passing to CEO..." << std::endl;
            nextApprover->approveRequest(amount);
        } else {
            std::cout << "Director: Cannot approve this amount" << std::endl;
        }
    }
};

class CEO : public Approver {
public:
    void approveRequest(double amount) override {
        std::cout << "CEO: Approved request of $" << amount << " (final approver)" << std::endl;
    }
};
