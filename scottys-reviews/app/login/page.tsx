// app/login/page.tsx
"use client";

import { Input } from "@/components/ui/input";
import { Button } from "@/components/ui/button";
import Link from "next/link";
import { useState } from "react";
import { signIn, useSession } from "next-auth/react";
import { useRouter } from "next/navigation";

export default function LoginPage() {
  const [formData, setFormData] = useState({ username: "", password: "" });
  const [error, setError] = useState("");
  const router = useRouter();
  const { data: session, status, update: updateSession } = useSession();

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();

    const res = await signIn("credentials", {
      redirect: false,
      netid: formData.username,
      password: formData.password,
    });

    if (res?.ok) {
      router.push("/profile"); // or your dashboard
    } else {
      setError("Invalid credentials");
    }
  };

  return (
    <>
      <div className="fixed inset-0 w-screen h-screen bg-[#d6e2ce] z-[-1]" />
      <div className="min-h-screen flex flex-col w-full full-width">
        <div className="relative w-full flex items-center pt-6 pb-6">
          <div className="absolute left-0 top-1/2 -translate-y-1/2 h-12 w-full bg-[#f8f1e4] rounded-r-lg z-0" />
          <div className="relative z-10 w-28 h-28 rounded-full border-4 border-[#f8f1e4] overflow-hidden flex items-center justify-center ml-8">
            <Link href="/home">
            <img src="/bearlogo.svg" alt="logo" className="w-full h-full object-cover rounded-full" />
            </Link>
          </div>
        </div>
        <div className="flex flex-1 items-center justify-center">
          <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-10 w-full max-w-md">
            <h1 className="text-4xl font-bold text-center mb-8 text-[#3a2c23]">Sign in</h1>
            <form onSubmit={handleSubmit}>
              <label htmlFor="username" className="block font-bold text-[#3a2c23] mb-2">NetID</label>
              <Input
                id="username"
                name="username"
                type="text"
                className="mb-4 bg-gray-200 w-full h-12 text-lg"
                required
                value={formData.username}
                onChange={(e) => setFormData({ ...formData, username: e.target.value })}
              />

              <label htmlFor="password" className="block font-bold text-[#3a2c23] mb-2">Password</label>
              <Input
                id="password"
                name="password"
                type="password"
                className="mb-6 bg-gray-200 w-full h-12 text-lg"
                required
                value={formData.password}
                onChange={(e) => setFormData({ ...formData, password: e.target.value })}
              />

              <Button type="submit" className="w-full !bg-[#3a2c23] text-white text-lg font-bold mb-4 !hover:bg-[#2a1c13]">
                Sign in
              </Button>
              {error && <p className="text-red-600 font-bold text-center mt-2">{error}</p>}
            </form>
            <div className="text-center mt-2 text-[#3a2c23]">
                Need an account? <Link href="/register" className="underline font-bold">Join now</Link>
                <br />
                <Link href="/forgot-password" className="underline font-bold text-sm inline-block mt-1">Forgot password?</Link>
            </div>
          </div>
        </div>
      </div>
    </>
  );
}
