#include <LiquidCrystal.h>

// Breadboard Parameters //

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int button1 = A1;
const int button2 = A2;
const int button3 = A3;
const int button4 = A4;

const int RGBRedPin = 9;
const int RGBBluePin = 10;
const int RGBGreenPin = 6;

// --- Functions: Test Board Inputs --- //

/* void button1press() // validated
{
  if (digitalRead(button1) == HIGH)
  {
    Serial.println("We pressed button 1.");
    delay(100);
  }
}

void button2press() // validated
{
  if (digitalRead(button2) == HIGH)
  {
    Serial.println("We pressed button 2.");
    delay(100);
  }
}

void button3press() // validated
{
  if (digitalRead(button3) == HIGH)
  {
    Serial.println("We pressed button 3.");
    delay(100);
  }
}

void button4press() // validated
{
  if (digitalRead(button4) == HIGH)
  {
    Serial.println("We pressed button 4.");
    delay(100);
  }
}

void RGBTest()
{ // validated
  digitalWrite(RGBRedPin, HIGH);
  delay(300);
  digitalWrite(RGBRedPin, LOW);
  digitalWrite(RGBGreenPin, HIGH);
  delay(300);
  digitalWrite(RGBGreenPin, LOW);
  digitalWrite(RGBBluePin, HIGH);
  delay(300);
  digitalWrite(RGBBluePin, LOW);
}

// LCD validated via setup() */

// --- Name and Species Traits --- //

String species[] = {"Griffin", "Dragon", "Phoenix"};
String namesGriffin[] = {"Talonclaw", "Stormcloud", "Windrider", "Thundercloud", "Moonbeak", "Mistwing", "Stormrider"};
String namesDragon[] = {"Silverclaw", "Stoneblade", "Frostmaw", "Tempest", "Cloudrend", "Stormshower", "Skyrender"};
String namesPhoenix[] = {"Fireheart", "Emberflare", "Dawnwing", "Ashfeather", "Stormcinder", "Flamewing", "Cindersoar"};
String parentJobs[] = {"guarding the city", "hunting", "providing transportation", "teaching", "building infrastructure", "conducting city repairs", "meeting with delegates", "holding council"};

// --- Ongoing Values --- //

String currentName = "";
String currentSpecies = "";
String job1 = "";
String job2 = "";
String currentNicknameName = "";

int currentAge = 0;
int currentTiredness = 0;
int currentHunger = 0;
int currentThirst = 0;
int currentHappiness = 0;
int currentTrust = 0;

int speciesIndex = 0;
int griffinNameIndex = 0;
int dragonNameIndex = 0;
int phoenixNameIndex = 0;
int job1Index = 0;
int job2Index = 0;

const int randomMin = 1;
const int randomMax = 5;
bool isGenerated = false;

// functions //

void nicknamePrompt()
{
  Serial.println("\nWould you like to give them a nickname?");
  Serial.println("Enter 'Y' for yes or 'N' for no:");

  // clear serial data; kept getting gibberish without periodic serial cleaning
  while (Serial.available())
  {
    Serial.read();
  }

  while (true) // runs indefinitely until loop is exited with break or return
  {
    while (!Serial.available())
    {
      delay(10);
    }

    // using readStringUntil to prevent buffer issues
    String nicknameInput = Serial.readStringUntil('\n');
    nicknameInput.trim();

    if (nicknameInput.equalsIgnoreCase("Y"))
    {
      Serial.println("What nickname would you like to give to " + String(currentName) + "?");

      // clear buffer before reading nickname
      while (Serial.available())
      {
        Serial.read();
      }

      while (!Serial.available())
      {
        delay(10);
      }

      // using readStringUntil for consistent input handling
      String userInputNickname = Serial.readStringUntil('\n');
      userInputNickname.trim();
      currentNicknameName = userInputNickname;

      Serial.println("You've nicknamed them " + currentNicknameName);
      break; // exit loop after successful nickname entry
    }

    else if (nicknameInput.equalsIgnoreCase("N"))
    {
      Serial.println("You're not choosing a nickname.");
      break; // exit loop after declining nickname
    }

    else
    {
      Serial.println("Invalid entry. Please enter 'Y' or 'N'.");
      // loop will repeat automatically
    }
  }
}

void generateTraits()
{
  if (digitalRead(button1) == HIGH && (!isGenerated))
  {
    delay(1000);

    Serial.flush();
    while (Serial.available())
      Serial.read();

    isGenerated = true;
    // Serial.println("Generating creature..."); debug

    currentAge = random(2, 5);
    currentTiredness = random(randomMin, randomMax);
    currentHunger = random(randomMin, randomMax);
    currentThirst = random(randomMin, randomMax);
    currentHappiness = random(randomMin, randomMax);
    currentTrust = random(randomMin, randomMax);

    speciesIndex = random(0, 3);
    currentSpecies = species[speciesIndex];

    switch (speciesIndex)
    {
    case 0: // Griffin
      // Serial.println("Griffin."); debug
      griffinNameIndex = random(0, 7);
      currentName = namesGriffin[griffinNameIndex];
      delay(50);
      break;

    case 1: // Dragon
      // Serial.println("Dragon."); debug
      dragonNameIndex = random(0, 7);
      currentName = namesDragon[dragonNameIndex];
      delay(50);
      break;

    case 2: // Phoenix
      // Serial.println("Phoenix."); debug
      phoenixNameIndex = random(0, 7);
      currentName = namesPhoenix[phoenixNameIndex];
      delay(50);
      break;
    }

    job1Index = random(0, 8);
    job2Index = random(0, 8);
    job1 = parentJobs[job1Index];
    job2 = parentJobs[job2Index];

    Serial.println();
    delay(50);
    Serial.print("You're providing care to a ");
    Serial.println(currentSpecies);
    delay(50);
    Serial.print("Their name is ");
    Serial.print(currentName);
    Serial.println(".");
    delay(50);
    Serial.print("They are ");
    Serial.print(currentAge);
    Serial.println(" years old.");
    delay(50);
    Serial.print("They are currently ");
    Serial.print(currentTiredness);
    Serial.print(", ");
    Serial.print(currentThirst);
    Serial.print(", and ");
    Serial.print(currentHunger);
    Serial.println(".");
    delay(50);
    Serial.print("They trust you ");
    Serial.print(currentTrust);
    Serial.println(".");
    delay(50);
    Serial.print("Their parents are currently ");
    Serial.print(job1);
    Serial.print(" and ");
    Serial.print(job2);
    Serial.println(".");
    delay(100);
    nicknamePrompt();
  }
}

void menuChooseAction()
{
  // program loops this menu to determine what user wants to do
}

void game1()
{
  // code for some kind of throw ball game
}

void game2()
{
  // code for dance party
}

void petCreature()
{
}

void feedCreature()
{
}

void napCreature()
{
}

void generateCurrentTraits()
{
}

// setup and loop //

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome.");
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(RGBBluePin, OUTPUT);
  pinMode(RGBGreenPin, OUTPUT);
  pinMode(RGBRedPin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop()
{
  generateTraits();
}