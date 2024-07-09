#include "Buttons.hpp"


Buttons::Buttons() {

    uint8_t matrixPinsA[] {BTN_MATRIX_A_L1, BTN_MATRIX_A_L2, BTN_MATRIX_A_R1, BTN_MATRIX_A_R2};
    btnA_ = new MyButtonMatrix2x2(BTN_MATRIX_A_DDR, BTN_MATRIX_A_PORT, BTN_MATRIX_A_PIN, matrixPinsA);

    uint8_t matrixPinsB[] {BTN_MATRIX_B_L1, BTN_MATRIX_B_L2, BTN_MATRIX_B_R1, BTN_MATRIX_B_R2};
    btnB_ = new MyButtonMatrix2x2(BTN_MATRIX_B_DDR, BTN_MATRIX_B_PORT, BTN_MATRIX_B_PIN, matrixPinsB);

    uint8_t matrixPinsC[] {BTN_MATRIX_C_L1, BTN_MATRIX_C_L2, BTN_MATRIX_C_R1, BTN_MATRIX_C_R2};
    btnC_ = new MyButtonMatrix2x2(BTN_MATRIX_C_DDR, BTN_MATRIX_C_PORT, BTN_MATRIX_C_PIN, matrixPinsC);

    uint8_t matrixPinsD[] {BTN_MATRIX_D_L1, BTN_MATRIX_D_L2, BTN_MATRIX_D_R1, BTN_MATRIX_D_R2};
    btnD_ = new MyButtonMatrix2x2(BTN_MATRIX_D_DDR, BTN_MATRIX_D_PORT, BTN_MATRIX_D_PIN, matrixPinsD);

}

Buttons::~Buttons() {
}

void Buttons::begin() {
}

void Buttons::listner() {

    uint8_t btnIndex = 0;
    const uint8_t btnNumber = 4;

    for (uint8_t i = 0; i < btnNumber; i++) {

        // check 2x2 Matrix A

        matrix_[btnIndex].pushed = btnA_->getButtonStatus(i).fallingEdge;
        btnIndex++; // for the next getter
    }

    for (uint8_t i = 0; i < btnNumber; i++) {

        // check 2x2 Matrix B

        matrix_[btnIndex].pushed = btnB_->getButtonStatus(i).fallingEdge;
        btnIndex++; // for the next getter
    }

    for (uint8_t i = 0; i < btnNumber; i++) {

        // check 2x2 Matrix C

        matrix_[btnIndex].pushed = btnC_->getButtonStatus(i).fallingEdge;
        btnIndex++; // for the next getter
    }

    for (uint8_t i = 0; i < btnNumber; i++) {

        // check 2x2 Matrix D

        matrix_[btnIndex].pushed = btnD_->getButtonStatus(i).fallingEdge;
        btnIndex++; // for the next getter
    }
}
