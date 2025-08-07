// types/next-auth.d.ts
import NextAuth from "next-auth";

declare module "next-auth" {
  interface Session {
    user: {
      id : string;
      netid: string;
      username: string;
    };
  }

  interface User {
    id: string;
    netid: string;
    username: string;
    password?: string | null;
  }

  interface JWT {
    id: string;
    netid?: string;
    username?: string;
  }
}
