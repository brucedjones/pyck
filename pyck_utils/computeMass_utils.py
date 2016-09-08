import math

def CalcMass(model, dx):
    print dx;
    numPhase = model.ReadSingleIntegerParameter("NumberOfPhases");
    #print numPhase;
    # smoothingKernelFunc = model.ReadSingleIntegerParameter("SmoothingKernelFunc");
    # if smoothingKernelFunc == 1:
    #     h = 1.3*dx;
    #     alpha_d = 15.0 / (7.0 * math.pi * h * h);
    #     R =0;
    #     w0 = alpha_d * (2.0 / 3.0 - (R * R) + 0.5 * (R * R * R));
    #     R = dx/h;
    #     w1 = alpha_d * (2.0 / 3.0 - (R * R) + 0.5 * (R * R * R));
    #     R = 2*dx/h;
    #     w2 =  alpha_d * 1.0 / 6.0 * (2.0 - R) * (2.0 - R) * (2.0 - R);
    #     R = sqrt(3) * dx /h;
    #     w3 =  alpha_d * 1.0 / 6.0 * (2.0 - R) * (2.0 - R) * (2.0 - R);
    #     density = model.ReadMultipleDoubleParameter("InitialDensity");
    #     mass = density/ (w0 + 6*w1 + 6*w2 + 6 *w3);
    # massStr = "";
    # for i in range(numPhase):
    #     massStr = massStr + str(mass[i]);
    # model.SetParameter("Mass", massStr);

