#include <WiFi.h>
 
const char * ssid = "SSID";
const char * password =  "password"; 
const char * host = "192.168.1.6";
int port = 6753;

int send = true;
int magnet = 27;
bool magnetState = false;
bool firstConnection = true;

WiFiServer server(5000);

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

String header;
 
void setup()
{
 
  Serial.begin(115200);

  pinMode(magnet, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}
 
void loop()
{
  WiFiClient client = server.available();
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    String currentLine = "";              
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {            
        char c = client.read();             
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html>");
            client.println("<html style='height:100%; margin:0px'>");
            client.println("    <head>");
            client.println("        <title>Remote Lock</title>");
            client.println("        <meta charset='UTF-8'>");
            client.println("        <meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("        <style>");
            client.println("            .button {");
            client.println("                display: inline-block;");
            client.println("                padding: 15px 25px;");
            client.println("                font-size: 50px;");
            client.println("                height:200px; ");
            client.println("                width:350px;");
            client.println("                cursor: pointer;");
            client.println("                text-align: center;");
            client.println("                text-decoration: none;");
            client.println("                outline: none;");
            client.println("                color: #fff;");

            if (firstConnection) {
              if (!magnetState) {   
              client.println("                background-color: firebrick;");
              client.println("                border: none;");
              client.println("                border-radius: 15px;");
              client.println("                box-shadow: 0 3px #999;");
              client.println("            }");
              client.println("            .button:hover {            ");
              client.println("                background-color: rgb(124, 27, 27);");
              client.println("            }");
              client.println("            .button:active {");
              client.println("                background-color: rgb(124, 27, 27);");
              client.println("                box-shadow: 0 3px #666;");
              client.println("                transform: translateY(4px);");
              client.println("            }");
              client.println("        </style>");
              client.println("    </head>");
              client.println("    <body style='height:100%; width:100%; margin:0px'>");
              client.println("        <div style='height: 100%; width:100%; display: flex; align-items: center; justify-content: center;'>");
              client.println("            <a href='/lock'><button class='button'>LOCK</button></a>");
              client.println("        </div>");
              client.println("    </body>");
              client.println("</html>");
              client.println();
              digitalWrite(magnet, LOW);
              magnetState = true;
              }
              else if (magnetState) {
                client.println("                background-color: mediumseagreen;");
                client.println("                border: none;");
                client.println("                border-radius: 15px;");
                client.println("                box-shadow: 0 3px #999;");
                client.println("            }");
                client.println("            .button:hover {            ");
                client.println("                background-color: rgb(44, 136, 85);");
                client.println("            }");
                client.println("            .button:active {");
                client.println("                background-color: rgb(44, 136, 85);");
                client.println("                box-shadow: 0 3px #666;");
                client.println("                transform: translateY(4px);");
                client.println("            }");
                client.println("        </style>");
                client.println("    </head>");
                client.println("    <body style='height:100%; width:100%; margin:0px'>");
                client.println("        <div style='height: 100%; width:100%; display: flex; align-items: center; justify-content: center;'>");
                client.println("            <a href='/unlock'><button class='button'>UNLOCK</button></a>");
                client.println("        </div>");
                client.println("    </body>");
                client.println("</html>");
                client.println();
                digitalWrite(magnet, HIGH);
                magnetState = false;
              }
              firstConnection = false;
              break;
            }
            else {
              if (header.indexOf("GET /unlock") >= 0) {
                client.println("                background-color: firebrick;");
                client.println("                border: none;");
                client.println("                border-radius: 15px;");
                client.println("                box-shadow: 0 3px #999;");
                client.println("            }");
                client.println("            .button:hover {            ");
                client.println("                background-color: rgb(124, 27, 27);");
                client.println("            }");
                client.println("            .button:active {");
                client.println("                background-color: rgb(124, 27, 27);");
                client.println("                box-shadow: 0 3px #666;");
                client.println("                transform: translateY(4px);");
                client.println("            }");
                client.println("        </style>");
                client.println("    </head>");
                client.println("    <body style='height:100%; width:100%; margin:0px'>");
                client.println("        <div style='height: 100%; width:100%; display: flex; align-items: center; justify-content: center;'>");
                client.println("            <a href='/lock'><button class='button'>LOCK</button></a>");
                client.println("        </div>");
                client.println("    </body>");
                client.println("</html>");
                client.println();
                digitalWrite(magnet, HIGH);
                magnetState = false;
              }
              else if (header.indexOf("GET /lock") >= 0) {
                client.println("                background-color: mediumseagreen;");
                client.println("                border: none;");
                client.println("                border-radius: 15px;");
                client.println("                box-shadow: 0 3px #999;");
                client.println("            }");
                client.println("            .button:hover {            ");
                client.println("                background-color: rgb(44, 136, 85);");
                client.println("            }");
                client.println("            .button:active {");
                client.println("                background-color: rgb(44, 136, 85);");
                client.println("                box-shadow: 0 3px #666;");
                client.println("                transform: translateY(4px);");
                client.println("            }");
                client.println("        </style>");
                client.println("    </head>");
                client.println("    <body style='height:100%; width:100%; margin:0px'>");
                client.println("        <div style='height: 100%; width:100%; display: flex; align-items: center; justify-content: center;'>");
                client.println("            <a href='/unlock'><button class='button'>UNLOCK</button></a>");
                client.println("        </div>");
                client.println("    </body>");
                client.println("</html>");
                client.println();
                digitalWrite(magnet, LOW);
                magnetState = true;
              }
              break;
            }
          }
        }
      }
    }
    firstConnection = true;
    header = "";
    client.stop();
  }
}