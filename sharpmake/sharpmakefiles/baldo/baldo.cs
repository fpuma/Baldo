using System.IO;

namespace Example.Projects
{
    [Sharpmake.Generate]
    public class Baldo : Puma.SharpmakeBase.IStaticLibrary
    {
        public Baldo()
        : base("Baldo", @"baldo")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);
            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");

            conf.AddPublicDependency<Utils>(target);
        }
    }
}