import { hashPassword } from "@/lib/bcrypt";
import { prisma } from "@/lib/prisma";
import { NextResponse } from "next/server";

export async function POST(req: Request) {
  const body = await req.json();
  const { netid, username, password } = body;

  if (!netid || !username || !password) {
    return NextResponse.json({ error: "Missing fields" }, { status: 400 });
  }

  const existing = await prisma.user.findUnique({ where: { netid } });
  if (existing) {
    return NextResponse.json({ error: "User already exists" }, { status: 400 });
  }

  const hashed = await hashPassword(password);
  await prisma.user.create({
    data: { netid, username, password: hashed },
  });

  return NextResponse.json({ message: "Account created" });
}
