using System.IO;

namespace Example.Projects
{
    [Sharpmake.Generate]
    public class Utils : Puma.SharpmakeBase.IHeaderOnly
    {
        public Utils()
        : base("Utils", @"submodules\utils")
        {}

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }
    }
}