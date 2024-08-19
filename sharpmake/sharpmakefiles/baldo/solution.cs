using System.IO;

namespace Example.Solutions
{
    [Sharpmake.Generate]
    public class BaldoSolution : Puma.SharpmakeBase.ISolution
    {
        public BaldoSolution()
            : base("Baldo")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Example.Projects.UnitTests>(target);
        }
    }
}