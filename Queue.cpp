#include<iostream>
#include<SFML/Graphics.hpp>
#include"Queue.h"
#include"Buttons.h"
#include"TextBox.h"
#include"InputData.h"
#include"Objects.h"

#define ENTER_KEY 13

Queue::Queue()
{
    front = nullptr;
    back = nullptr;
    Size = 0;
}

Queue::~Queue()
{
    while (front != nullptr)
    {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

void Queue::Add(std::string data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->next = nullptr;

    if (front == nullptr)
    {
        front = temp;
        back = temp;
    }
    else
    {
        back->next = temp;
        back = temp;
    }
    Size++;
}

void Queue::Remove()
{
    std::string data = front->data;
    Node* temp = front;
    front = front->next;
    if (front == nullptr) back = nullptr;
    delete temp;
    Size--;
}

bool Queue::isFull()
{
    return Size == 7;
}

bool Queue::isEmpty()
{
    return front == nullptr;
}

void Queue::Print(sf::RenderWindow& window)
{
    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    sf::Color TextColor(64, 140, 124);

    sf::Text Data;
    Data.setFont(arial);
    Data.setCharacterSize(15);
    Data.sf::Text::setFillColor(TextColor);
    Data.setStyle(sf::Text::Bold);

    Node* current = front;
    int i = 0;
    while (current != nullptr)
    {
        Data.setString(current->data);
        Data.setPosition({ (float)240 + i * (150), 292.5 });
        window.draw(Data);
        current = current->next;
        i++;
    }
}
void Queue::Set(std::vector<std::string> X)
{
    front = nullptr;
    back = nullptr;
    Size = 0;
    for (int i = 0; i < X.size(); i++)
        Add(X[i]);
}

int Queue::GetSize() 
{
    return Size;
}

void Set(Queue& X, std::vector<std::string> Y)
{
    X.Set(Y);
}

void Add(Queue& X, std::string Y)
{
    X.Add(Y);
}

void Remove(Queue& X)
{
    X.Remove();
}

std::string GetData(sf::Event Events, sf::RenderWindow& window, Button btn[], int Nbtn, int X, int& Done, Queue& Example)
{
    X--;

    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    sf::Color ScreenColor(238, 137, 128);
    sf::Color OutColor(241, 70, 102);
    sf::Color BoxColor(255, 220, 195);
    sf::Color TextColor(64, 140, 124);

    sf::Text Note1;
    Note1.setFont(arial);
    Note1.setCharacterSize(20);
    Note1.setString("Input your data then press enter key!");
    Note1.sf::Text::setFillColor(sf::Color::Cyan);
    Note1.setPosition({ 500, 50 });
    Note1.setStyle(sf::Text::Bold);

    Textbox Textbox1(15, TextColor, true);
    Textbox1.setFont(arial);
    Textbox1.setLimit(false);
    Textbox1.setPosition(btn[X].getPosition());

    sf::RectangleShape Box;
    Box.setSize({ 160, 40 });
    Box.setFillColor(BoxColor);
    Box.setPosition(btn[X].getPosition());
    Box.setOutlineThickness(3);
    Box.setOutlineColor(OutColor);

    sf::Text Head;
    Head.setFont(arial);
    Head.setCharacterSize(20);
    Head.setString("Head/");
    Head.sf::Text::setFillColor(sf::Color::Cyan);
    Head.setStyle(sf::Text::Bold);

    sf::Text Tail;
    Tail.setFont(arial);
    Tail.setCharacterSize(20);
    Tail.setString("Tail/");
    Tail.sf::Text::setFillColor(sf::Color::Cyan);
    Tail.setStyle(sf::Text::Bold);

    Button btnHome("Home", { 100, 50 }, 15, sf::Color::Cyan, TextColor, OutColor, 5);
    btnHome.setPos({ 1200, 0 });
    btnHome.setFont(arial);

    while (window.isOpen())
    {
        while (window.pollEvent(Events))
        {
            switch (Events.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (btnHome.isMouseOver(window))
                {
                    Done = -1;
                    return "";
                }
                else
                {
                    for (int i = 0; i < Nbtn; i++)
                        if (btn[i].isMouseOver(window))
                        {
                            Done = i + 1;
                            return "";
                        }
                }
                break;

            case sf::Event::TextEntered:
                Done = 0;
                if (Events.text.unicode == ENTER_KEY) return Textbox1.getText();
                Textbox1.typeOn(Events);
                break;
            }
        }

        if (btnHome.isMouseOver(window))
        {
            btnHome.setBackColor(sf::Color::White);
        }
        else
        {
            btnHome.setBackColor(sf::Color::Cyan);
            for (int i = 0; i < Nbtn; i++)
                if (btn[i].isMouseOver(window))
                    btn[i].setBackColor(sf::Color::White);
                else btn[i].setBackColor(BoxColor);
        }

        window.clear(ScreenColor);

        for (int i = 0; i < Nbtn; i++)
            btn[i].drawto(window);
        btnHome.drawto(window);
        window.draw(Box);
        Textbox1.drawto(window);
        window.draw(Note1);

        PrintArrow(Example.GetSize() - 1, window);
        PrintBox(Example.GetSize(), window);
        Example.Print(window);

        if (Example.GetSize() > 0)
        {
            if (Example.GetSize() == 1)
            {
                Head.setString("Head/Tail/");
                Head.setPosition({ 225, 372.5 });
                window.draw(Head);
            }
            else
            {
                Tail.setPosition({ (float)240 + (Example.GetSize() - 1) * 150, 372.5 });
                Head.setPosition({ 240, 372.5 });
                Head.setString("Head/");
                window.draw(Head);
                window.draw(Tail);
            }
        }

        window.display();
    }
    Done = 0;
    return "";
}

void QueueClient(sf::Event Events, sf::RenderWindow& window)
{
    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    sf::Color ScreenColor(238, 137, 128);
    sf::Color OutColor(241, 70, 102);
    sf::Color BoxColor(255, 220, 195);
    sf::Color TextColor(64, 140, 124);

    Button btn[10];
    for (int i = 0; i < 5; i++)
    {
        btn[i] = Button("", { 160, 40 }, 15, BoxColor, TextColor, OutColor, 3);
        btn[i].setPos({ 10, (float)10 + i * 56 });
        btn[i].setFont(arial);
    }
    btn[0].setString("Init from file");
    btn[1].setString("Randomized data");
    btn[2].setString("Add");
    btn[3].setString("Remove");
    btn[4].setString("Clear");

    sf::Text Warnings1;
    Warnings1.setFont(arial);
    Warnings1.setCharacterSize(20);
    Warnings1.setString("You can not have more than 7 elements!");
    Warnings1.sf::Text::setFillColor(sf::Color::Cyan);
    Warnings1.setPosition({ 500, 50 });
    Warnings1.setStyle(sf::Text::Bold);

    sf::Text Warnings2;
    Warnings2.setFont(arial);
    Warnings2.setCharacterSize(20);
    Warnings2.setString("It is empty!");
    Warnings2.sf::Text::setFillColor(sf::Color::Cyan);
    Warnings2.setPosition({ 500, 50 });
    Warnings2.setStyle(sf::Text::Bold);
    
    sf::Text Head;
    Head.setFont(arial);
    Head.setCharacterSize(20);
    Head.setString("Head/");
    Head.sf::Text::setFillColor(sf::Color::Cyan);
    Head.setStyle(sf::Text::Bold);

    sf::Text Tail;
    Tail.setFont(arial);
    Tail.setCharacterSize(20);
    Tail.setString("Tail/");
    Tail.sf::Text::setFillColor(sf::Color::Cyan);
    Tail.setStyle(sf::Text::Bold);

    Button btnHome("Home", { 100, 50 }, 15, sf::Color::Cyan, TextColor, OutColor, 5);
    btnHome.setPos({ 1200, 0 });
    btnHome.setFont(arial);

    Queue Example;
    Set(Example, Initialize());

    int Type = 0;
    int Done = 0;

    while (window.isOpen())
    {

        while (window.pollEvent(Events))
        {
            if (Done != 0)
            {
                const char* Path = nullptr;
                switch (Done)
                {
                case 1:
                    Type = 0;
                    Done = 0;
                    Path = FindPath();
                    if (Path != nullptr) Set(Example, ReadFromFile(Path));
                    break;

                case 2:
                    Type = 0;
                    Done = 0;
                    Set(Example, Initialize());
                    break;

                case 3:
                    if (Example.isFull())
                    {
                        Type = 1;
                        Done = 0;
                    }
                    else
                    {
                        Type = 0;
                        Done = 3;
                        std::string X = GetData(Events, window, btn, 5, 3, Done, Example);
                        if (Done != 0) break;
                        Add(Example, X);
                        window.clear(ScreenColor);
                        PrintArrow(Example.GetSize() - 2, window);
                        PrintBox(Example.GetSize(), window);
                        Example.Print(window);
                        btnHome.drawto(window);
                        for (int i = 0; i < 5; i++)
                            btn[i].drawto(window);
                        if (Example.GetSize() == 1)
                        {
                            Head.setString("Head/Tail/");
                            Head.setPosition({ 225, 372.5 });
                            window.draw(Head);
                        }
                        else
                        {
                            Tail.setPosition({ (float)240 + (Example.GetSize() - 1) * 150, 372.5 });
                            Head.setPosition({ 240, 372.5 });
                            Head.setString("Head/");
                            window.draw(Head);
                            window.draw(Tail);
                        }
                        window.display();
                        sf::sleep(sf::seconds(1));
                    }
                    break;

                case 4:
                    if (Example.isEmpty())
                    {
                        Type = 2;
                        Done = 0;
                    }
                    else
                    {
                        window.clear(ScreenColor);
                        if (Example.GetSize() > 0)
                        {
                            if (Example.GetSize() == 1)
                            {
                                Head.setString("Head/Tail/");
                                Head.setPosition({ 225, 372.5 });
                                window.draw(Head);
                            }
                            else
                            {
                                Tail.setPosition({ (float)240 + (Example.GetSize() - 1) * 150, 372.5 });
                                Head.setPosition({ 240, 372.5 });
                                Head.setString("Head/");
                                window.draw(Head);
                                window.draw(Tail);
                            }
                        }
                        PrintArrow(Example.GetSize() - 1, 0, 8, window);
                        PrintBox(Example.GetSize(), window);
                        Example.Print(window);
                        btnHome.drawto(window);
                        for (int i = 0; i < 5; i++)
                            btn[i].drawto(window);

                        window.display();
                        sf::sleep(sf::seconds(1));
                        Remove(Example);
                        Type = 0;
                        Done = 0;
                    }
                    break;

                case 5:
                    Example.Set({});
                    Done = 0;
                    break;

                case -1:
                    return;
                }
            }
            else
            {
                switch (Events.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (btnHome.isMouseOver(window))
                    {
                        return;
                    }
                    else
                    {
                        for (int i = 0; i < 5; i++)
                            if (btn[i].isMouseOver(window))
                            {
                                Done = i + 1;
                                break;
                            }
                    }
                }
            }
        }

        if (btnHome.isMouseOver(window))
        {
            btnHome.setBackColor(sf::Color::White);
        }
        else
        {
            btnHome.setBackColor(sf::Color::Cyan);
            for (int i = 0; i < 5; i++)
                if (btn[i].isMouseOver(window))
                    btn[i].setBackColor(sf::Color::White);
                else btn[i].setBackColor(BoxColor);
        }

        window.clear(ScreenColor);

        btnHome.drawto(window);
        PrintArrow(Example.GetSize() - 1, window);
        PrintBox(Example.GetSize(), window);
        Example.Print(window);

        if (Example.GetSize() > 0)
        {
            if (Example.GetSize() == 1)
            {
                Head.setString("Head/Tail/");
                Head.setPosition({ 225, 372.5 });
                window.draw(Head);
            }
            else
            {
                Tail.setPosition({ (float)240 + (Example.GetSize() - 1) * 150, 372.5 });
                Head.setPosition({ 240, 372.5 });
                Head.setString("Head/");
                window.draw(Head);
                window.draw(Tail);
            }
        }

        for (int i = 0; i < 5; i++)
            btn[i].drawto(window);

        if (Type == 1) window.draw(Warnings1);
        else if (Type == 2) window.draw(Warnings2);

        window.display();

    }
}