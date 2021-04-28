namespace OracleImpl
{
    extern dpiContext* gDpiContext;
    extern dpiErrorInfo gErrorInfo;
    inline std::string oracleErrorMsg()
    {
        if (gDpiContext)
        {
            dpiContext_getError(gDpiContext, &gErrorInfo);
        }

        char buffer[2048] = { 0 };
        snprintf(buffer, sizeof(buffer) - 1, "%.*s (%s: %s), offset: %u\n", gErrorInfo.messageLength, gErrorInfo.message, gErrorInfo.fnName, gErrorInfo.action, gErrorInfo.offset);
        return std::string(buffer);
    }
}