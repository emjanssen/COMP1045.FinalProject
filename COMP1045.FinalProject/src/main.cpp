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

/*
void button1press() // validated
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

// LCD validated via setup()
*/

// --- Name and Species Traits --- //

const char* species[] = {"Griffin", "Dragon", "Phoenix"};
const char* namesGriffin[] = {"Talonclaw", "Stormcloud", "Windrider", "Thundercloud", "Moonbeak", "Mistwing", "Stormrider"};
const char* namesDragon[] = {"Silverclaw", "Stoneblade", "Frostmaw", "Tempest", "Cloudrend", "Stormshower", "Skyrender"};
const char* namesPhoenix[] = {"Fireheart", "Emberflare", "Dawnwing", "Ashfeather", "Stormcinder", "Flamewing", "Cindersoar"};
const char* parentJobs[] = {"guarding the city", "hunting", "providing transportation", "teaching", "building infrastructure", "conducting city repairs", "meeting with delegates", "holding council"};

// --- Ongoing Values --- //

const char* currentName = "";
const char* currentSpecies = "";
String currentNicknameName = "";
const char* job1 = "";
const char* job2 = "";

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
  while (true)
  {
    Serial.println("\nWould you like to give them a nickname?");
    Serial.println("Enter 'Y' for yes or 'N' for no:");

    while (Serial.available()) Serial.read(); // Clear any existing data

    while (!Serial.available()) delay(10);

    char nicknamePromptResponse = (char)Serial.read();

    if (nicknamePromptResponse == 'Y' || nicknamePromptResponse == 'y')
    {
      Serial.print("What would you like to nickname ");
      Serial.print(currentName);
      Serial.println("?");

      String nicknameInputAsString = "";

      while (!Serial.available()) delay(10);

      // Wait until the user finishes typing (newline or timeout)
      unsigned long startTime = millis();
      while (millis() - startTime < 1000) // wait 1 second for input to complete
      {
        while (Serial.available() > 0)
        {
          char c = Serial.read();
          if (c == '\n' || c == '\r') break;
          nicknameInputAsString += c;
          startTime = millis(); // reset timer on input
        }
      }

      currentNicknameName = nicknameInputAsString;
      Serial.print("You've nicknamed them ");
      Serial.println(currentNicknameName);

      break;
    }
    else if (nicknamePromptResponse == 'N' || nicknamePromptResponse == 'n')
    {
      Serial.println("You're not choosing a nickname.");
      break;
    }
    else
    {
      Serial.print("Invalid entry: ");
      Serial.println(nicknamePromptResponse);
      Serial.println("Please enter 'Y' or 'N'.");
    }
  }

  Serial.println("Please press button 2.");
}
void generateTraits()
{
  if (digitalRead(button1) == HIGH && (!isGenerated))
  {
    delay(1000); // 1 second delay because i don't want multiple button presses register, cause that could mean multiple creatures generated

    // set to true so another creature can't be generated if the button is pressed again
    isGenerated = true;

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
      griffinNameIndex = random(0, 7);
      currentName = namesGriffin[griffinNameIndex];
      delay(50);
      break;

    case 1: // Dragon
      dragonNameIndex = random(0, 7);
      currentName = namesDragon[dragonNameIndex];
      delay(50);
      break;

    case 2: // Phoenix
      phoenixNameIndex = random(0, 7);
      currentName = namesPhoenix[phoenixNameIndex];
      delay(50);
      break;
    }

    displayCreature();

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
    delay(100); // Extra delay before prompt

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(currentSpecies);
    lcd.setCursor(0, 1);
    lcd.print(currentName);

    nicknamePrompt();
  }

  else if (digitalRead(button1) == HIGH && (isGenerated))
  {
    delay(50);
    Serial.print("You're already caring for ");
    if (currentNicknameName != "")
      Serial.print(currentNicknameName);
    else
      Serial.print(currentName);
    Serial.println(".");
    delay(500);
  }
}

void displayCreature() {
  // Only clear and update the LCD once when the species is set
  if (currentSpecies == "Griffin") {
    lcd.setCursor(0, 0);
    lcd.print("<^•.•^>");
    lcd.setCursor(0, 1);
    lcd.print("//__|\\");
  }
  else if (currentSpecies == "Dragon") {
    lcd.setCursor(0, 0);
    lcd.print("~^._.^~");
    lcd.setCursor(0, 1);
    lcd.print(" /|\\");
  }
  else if (currentSpecies == "Phoenix") {
    lcd.setCursor(0, 0);
    lcd.print("^,^");
    lcd.setCursor(0, 1);
    lcd.print(" |||");
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
