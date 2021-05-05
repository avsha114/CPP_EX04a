#include "doctest.h"

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;

TEST_CASE("Board")
{
    Board board;

    CHECK_EQ(board[Algiers], 0);
    CHECK_EQ(board[Algiers]=2, 2);
    CHECK_EQ(board[Algiers], 2);
    CHECK_EQ(board.is_clean(), false);
    CHECK_EQ(board[Algiers]=0, 0);
    CHECK_EQ(board.is_clean(), true);
}

TEST_CASE("OperationsExpert")
{
    Board board;

    OperationsExpert player{board, Delhi};
    player.take_card(Delhi);

    CHECK_NOTHROW(player.build()); //Test regular player build()
    CHECK_NOTHROW(player.drive(Kolkata));
    CHECK_NOTHROW(player.build());
    CHECK_NOTHROW(player.drive(HongKong));
    CHECK_NOTHROW(player.build());
    CHECK_NOTHROW(player.build()); //Check that building again doesn't throw an exception
    
    //Test that building in Delhi didn't throw the Delhi card:
    CHECK_NOTHROW(player.fly_direct(Delhi));
}

TEST_CASE("Dispatcher")
{
    Board board;

    Dispatcher player{board, Bogota};
    player.take_card(Bogota)
            .take_card(Washington)
            .take_card(Istanbul);
    
    //Build a research center:
    CHECK_NOTHROW(player.build());
    CHECK_NOTHROW(player.build()); //Check that building again doesn't throw an exception
    
    //Check if Dispatcher can fly to other Cities:
    CHECK_NOTHROW(player.fly_direct(Washington));
    CHECK_NOTHROW(player.build());
    CHECK_NOTHROW(player.fly_direct(Istanbul));

    //Check that dispatcher CAN'T fly without a research center:
    CHECK_THROWS(player.fly_direct(Santiago));
}

TEST_CASE("Scientist")
{
    Board board;

    //Increase disease levels:
    board[Beijing] = board[Moscow] = board[NewYork] = board[LosAngeles] = 10;

    //Build research centers:
    OperationsExpert builder{board, Beijing};
    builder.take_card(NewYork).take_card(Moscow).take_card(LosAngeles);
    builder.build();
    builder.fly_direct(NewYork);    builder.build();
    builder.fly_direct(Moscow);     builder.build();
    builder.fly_direct(LosAngeles); builder.build();

    Scientist player1{board, Beijing, 1}; //Red city
    Scientist player2{board, NewYork, 2}; //Blue city
    Scientist player3{board, Moscow, 3}; //Black city
    Scientist player4{board, LosAngeles, 4}; //Yellow city

    player1.take_card(Essen); // Blue card
    player2.take_card(Osaka).take_card(Sydney); //Red cards
    player3.take_card(Mumbai)
        .take_card(Riyadh)
        .take_card(Tehran); //Black cards
    player4.take_card(Santiago)
        .take_card(SaoPaulo)
        .take_card(MexicoCity)
        .take_card(Khartoum); //Yellow cards

    //Check disccover_cure:
    player1.discover_cure(Blue);
    player2.discover_cure(Red);
    player3.discover_cure(Black);
    player4.discover_cure(Yellow);

    //Treat the diseases:
    CHECK_NOTHROW(player1.treat(Beijing));
    CHECK_NOTHROW(player2.treat(NewYork));
    CHECK_NOTHROW(player3.treat(Moscow));
    CHECK_NOTHROW(player4.treat(LosAngeles));

    //Check that the diseases were cured:
    CHECK_EQ(board[Beijing], 0);
    CHECK_EQ(board[NewYork], 0);
    CHECK_EQ(board[Moscow], 0);
    CHECK_EQ(board[LosAngeles], 0);

    //Check that the cards were thrown:
    CHECK_THROWS(player1.discover_cure(Red));
    CHECK_THROWS(player2.discover_cure(Blue));
    CHECK_THROWS(player3.discover_cure(Black));
    CHECK_THROWS(player4.discover_cure(Yellow));
}

TEST_CASE("Researcher"){
    Board board;

    //Increase disease levels:
    board[Beijing] = board[Moscow] = board[NewYork] = board[LosAngeles] = 10;

    Researcher player1{board, Beijing}; //Red city
    Researcher player2{board, NewYork}; //Blue city
    Researcher player3{board, Moscow}; //Black city
    Researcher player4{board, LosAngeles}; //Yellow city

    player1.take_card(Osaka).take_card(HoChiMinhCity)
            .take_card(Manila).take_card(Sydney).take_card(Taipei); //5 Red cards
    player2.take_card(Essen).take_card(Chicago)
            .take_card(Washington).take_card(Paris).take_card(Atlanta); //5 Blue cards
    player3.take_card(Mumbai).take_card(Riyadh)
            .take_card(Tehran).take_card(Kolkata).take_card(Chennai); //5 Black cards
    player4.take_card(Santiago).take_card(SaoPaulo)
            .take_card(MexicoCity).take_card(Khartoum).take_card(Lima); //5 Yellow cards

    //Check disccover_cure:
    player1.discover_cure(Red);
    player2.discover_cure(Blue);
    player3.discover_cure(Black);
    player4.discover_cure(Yellow);

    //Treat the diseases:
    CHECK_NOTHROW(player1.treat(Beijing));
    CHECK_NOTHROW(player2.treat(NewYork));
    CHECK_NOTHROW(player3.treat(Moscow));
    CHECK_NOTHROW(player4.treat(LosAngeles));

    //Check that the diseases were cured:
    CHECK_EQ(board[Beijing], 0);
    CHECK_EQ(board[NewYork], 0);
    CHECK_EQ(board[Moscow], 0);
    CHECK_EQ(board[LosAngeles], 0);

    //Check that the cards were thrown:
    CHECK_THROWS(player1.discover_cure(Red));
    CHECK_THROWS(player2.discover_cure(Blue));
    CHECK_THROWS(player3.discover_cure(Black));
    CHECK_THROWS(player4.discover_cure(Yellow));
}

TEST_CASE("Medic"){
    Board board;

    //Increase disease levels:
    board[Madrid] = board[Milan] = board[Paris] = 10;

    Medic player{board, Madrid};
    Researcher Researcher{board, Paris}; //To discover cure
    Researcher.take_card(Madrid).take_card(Milan)
        .take_card(Paris).take_card(Chicago).take_card(Montreal); //Take 5 blue cards
    
    //Check treat without a cure:
    player.treat(Madrid);
    CHECK_EQ(board[Madrid], 0);

    //Find a cure for blue cities:
    Researcher.discover_cure(Blue);

    //Check that Medic is curing diseases when arriving to a blue city:
    player.drive(Paris);
    CHECK_EQ(board[Paris], 0);
    player.drive(Milan);
    CHECK_EQ(board[Milan], 0);
}

TEST_CASE("Virologist"){
    Board board;

    //Increase disease levels:
    board[Seoul] = board[Tokyo] = 10;

    Virologist player1{board, StPetersburg};
    player1.take_card(Seoul).take_card(Tokyo);

    Researcher researcher{board, Paris}; //To discover cure
    researcher.take_card(Sydney).take_card(Taipei)
        .take_card(Jakarta).take_card(Manila).take_card(Osaka);
    
    //Check treat:
    player1.treat(Seoul);
    CHECK_EQ(board[Seoul], 9);

    researcher.discover_cure(Red);
    player1.treat(Tokyo);
    CHECK_EQ(board[Tokyo], 0);
}

TEST_CASE("GeneSplicer"){
    Board board;

    //Increase disease levels:
    board[BuenosAires] = 10;

    GeneSplicer player{board, BuenosAires};
    OperationsExpert builder{board, BuenosAires};

    //Build a research center:
    builder.build();
    
    //Take cards in different colors:
    player.take_card(Delhi).take_card(Jakarta)
        .take_card(Kinshasa).take_card(London).take_card(Montreal);

    //discover Yellow cure:
    player.discover_cure(Yellow);

    //Check that the cure works:
    player.treat(BuenosAires);
    CHECK_EQ(board[BuenosAires], 0);
}

TEST_CASE("FieldDoctor"){
    Board board;

    //Increase disease levels:
    board[Johannesburg] = board[Kinshasa] = board[Khartoum] = 10;

    FieldDoctor player{board, Johannesburg};

    player.take_card(Kinshasa).take_card(Khartoum); //Take adjacent cities cards.

    //Check treat in Johannesburn and it's adjacent cities:
    CHECK_NOTHROW(player.treat(Johannesburg));
    CHECK_NOTHROW(player.treat(Kinshasa));
    CHECK_NOTHROW(player.treat(Khartoum));

    CHECK_EQ(board[Johannesburg], 9);
    CHECK_EQ(board[Kinshasa], 9);    
    CHECK_EQ(board[Khartoum], 9);

    //Check that the cards were not thrown:
    CHECK_NOTHROW(player.fly_direct(Kinshasa).fly_direct(Khartoum));
}