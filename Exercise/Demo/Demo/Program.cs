// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");
string A = "Points[i][j]";
string B = "Points[i+1][j]";
string C = "Points[i][j+1]";
string D = "Points[i+1][j+1]";
Console.WriteLine("AddQuad(" + A + "," + B + "," + D + "," + C + ");");
Console.WriteLine("AddQuad(" + A + "," + B + "," + C + "," + D + ");");
Console.WriteLine("AddQuad(" + A + "," + C + "," + B + "," + D + ");");
Console.WriteLine("AddQuad(" + A + "," + C + "," + D + "," + B + ");");
Console.WriteLine("AddQuad(" + A + "," + D + "," + B + "," + C + ");");
Console.WriteLine("AddQuad(" + A + "," + D + "," + C + "," + B + ");");

Console.WriteLine("AddQuad(" + B + "," + A + "," + C + "," + D + ");");
Console.WriteLine("AddQuad(" + B + "," + A + "," + D + "," + C + ");");
Console.WriteLine("AddQuad(" + B + "," + D + "," + C + "," + A + ");");
Console.WriteLine("AddQuad(" + B + "," + D + "," + A + "," + C + ");");
Console.WriteLine("AddQuad(" + B + "," + C + "," + A + "," + D + ");");
Console.WriteLine("AddQuad(" + B + "," + C + "," + D + "," + A + ");");

Console.WriteLine("AddQuad(" + C + "," + A + "," + B + "," + D + ");");
Console.WriteLine("AddQuad(" + C + "," + A + "," + D + "," + B + ");");
Console.WriteLine("AddQuad(" + C + "," + B + "," + A + "," + D + ");");
Console.WriteLine("AddQuad(" + C + "," + B + "," + D + "," + A + ");");
Console.WriteLine("AddQuad(" + C + "," + D + "," + A + "," + B + ");");
Console.WriteLine("AddQuad(" + C + "," + D + "," + B + "," + A + ");");

Console.WriteLine("AddQuad(" + D + "," + A + "," + C + "," + B + ");");
Console.WriteLine("AddQuad(" + D + "," + A + "," + B + "," + C + ");");
Console.WriteLine("AddQuad(" + D + "," + B + "," + C + "," + A + ");");
Console.WriteLine("AddQuad(" + D + "," + B + "," + A + "," + C + ");");
Console.WriteLine("AddQuad(" + D + "," + C + "," + A + "," + B + ");");
Console.WriteLine("AddQuad(" + D + "," + C + "," + B + "," + A + ");");

