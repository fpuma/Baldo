using System.IO;

[module: Sharpmake.Include(@"..\..\sharpmakeutils\utils\*")]

//Examples
[module: Sharpmake.Include(@"..\baldo\*")]

public static class SharpmakeMainClass
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments sharpmakeArgs)
    {
        sharpmakeArgs.Generate<Example.Solutions.BaldoSolution>();
    }
}

