"use client";

import { Input } from "@/components/ui/input";
import { Button } from "@/components/ui/button";
import Link from "next/link";
import { useState } from "react";
import { useRouter } from "next/navigation";

export default function RegisterPage() {
  const router = useRouter();
  const [formData, setFormData] = useState({
    username: "",
    netid: "",
    password: "",
    major: "",
    classStanding: "",
    gradYear: ""
  });
  const [error, setError] = useState("");

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();

    const res = await fetch("/api/register", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        ...formData,
        expectedGradYear: parseInt(formData.gradYear),
        status: formData.classStanding,
      }),
    });

    if (res.ok) {
      router.push("/login?created=true");
    } else {
      const data = await res.json();
      setError(data.error || "Something went wrong.");
    }
  };

  return (
    <>
      <div className="fixed inset-0 w-screen h-screen bg-[#d6e2ce] z-[-1]" />

      <div className="relative w-screen flex items-center pt-6 pb-6 left-1/2 right-1/2 -translate-x-1/2">
        <div className="absolute left-0 top-1/2 -translate-y-1/2 h-12 w-full bg-[#f8f1e4] rounded-r-lg z-0" />
        <div className="relative z-10 w-28 h-28 rounded-full border-4 border-[#f8f1e4] bg-white overflow-hidden flex items-center justify-center ml-8">
          <Link href="/home">
          <img
            src="/bearlogo.svg"
            alt="logo"
            className="w-full h-full object-cover"
          />
          </Link>
        </div>
      </div>

      <div className="flex flex-1 items-center justify-center">
        <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-10 w-full max-w-md">
          <h1 className="text-3xl font-bold text-[#3a2c23] mb-8 text-center">Create Your Account</h1>
          <form onSubmit={handleSubmit}>
            {error && <p className="text-red-600 font-bold text-center mb-4">{error}</p>}

            {[
              { id: "username", label: "Dispaly Name" },
              { id: "netid", label: "Netid" },
              { id: "password", label: "Password", type: "password" },
              { id: "major", label: "Major" },
              { id: "classStanding", label: "Current class standing" },
              { id: "gradYear", label: "Expected Graduation year" },
            ].map(({ id, label, type }) => (
              <div key={id}>
                <label className="block font-bold text-[#3a2c23] mb-2" htmlFor={id}>{label}</label>
                <Input
                  id={id}
                  name={id}
                  type={type || "text"}
                  className="mb-4 bg-gray-200 w-full h-12 text-lg"
                  required
                  value={(formData as any)[id]}
                  onChange={(e) => setFormData({ ...formData, [id]: e.target.value })}
                />
              </div>
            ))}

            <Button
              type="submit"
              className="w-full !bg-[#3a2c23] text-white text-lg font-bold mb-4 !hover:bg-[#2a1c13]"
            >
              Create Account
            </Button>
          </form>
        </div>
      </div>
    </>
  );
}
