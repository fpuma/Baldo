using System.IO;


namespace Example.Projects
{
    [Sharpmake.Generate]
    class UnitTests : Puma.SharpmakeBase.IApplication
    {
        public UnitTests()
            : base("UnitTests", @"tests\unittests")
        { 
        }

        public override void ConfigureAll(Sharpmake.Project.Configuration conf, Sharpmake.Target target )
        {
            base.ConfigureAll(conf, target);
            conf.AddPrivateDependency<Baldo>(target);
        }
    }
}