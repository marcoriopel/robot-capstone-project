/*
 * Nom: bouton.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

const uint8_t PIND0 = 0 
const uint8_t PIND1 = 1 
const uint8_t PIND2 = 2 
const uint8_t PIND3 = 3 
const uint8_t PIND4 = 4 
const uint8_t PIND5 = 5 
const uint8_t PIND6 = 6 
const uint8_t PIND7 = 7 


void ajustementPWM ( uint8_t pourcentageOCR1A, pourcentageOCR1B ) 
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = (255 * pourcentageOCR1A) / 100 ;

    OCR1B = (255 * pourcentageOCR1B) / 100 ;


    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A |= (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (1 << WGM10) ;

    TCCR1B |=  (1 << CS11) ;

    TCCR1C |= 0;

}



void ajustementDirectionRoues ( bool roueAAvance, bool roueBAvance ) 
{
    PORTD |=   roueAAvance << PIND7 | roueAAvance << PIND6
    PORTD &= ~(roueAAvance << PIND7 | roueAAvance << PIND6)
}



void allumerMoteur(int pourcentage, int frequence, double duree)
{
    int allumer = pourcentage;
    int fermer = 100 - allumer;

    uint16_t nDelayLoop2 = ((1 / frequence) / 100) / 0.0000005

    for (int i = 0; i < (duree * frequence); ++i)
    {
        for (int i = 0; i <= allumer; ++i)
        {
            PORTB = MOTEUR_ALLUME;
            _delay_loop_2(nDelayLoop2);
        }
        for (int i = 0; i <= fermer; ++i)
        {
            PORTB = MOTEUR_ETEINT;
            _delay_loop_2(nDelayLoop2);
        }
    }
}